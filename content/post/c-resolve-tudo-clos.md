---
categories: [ "code" ]
date: "2019-05-17"
tags: [ "draft",  ]
title: "C Resolve Tudo Clos"
---
Continuando nossa série, conforme sugerido pelo @colemaker do grupo C/C++/42/Império do Brasil, a próxima ideia a ser implementada em C é o sistema polimórfico de chamadas do Lisp orientado a objetos. Esse sistema permite realizar a seguinte manobra:

    (defgeneric thing(x y))
    
    ;; BAR inhherits FOO
    (defclass foo()())
    
    (defmethod thing ((x foo) (y foo))
      (format t "Both are of type FOO~%"))
    
    (def method thing ((x bar) (y foo))
      (format t "X is a BAR, Y is a FOO. Next...~%")
      (call-next-method))
    
    (def method thing ((x foo) (y bar))
      (format t "X is a FOO, Y is a BAR. Next...~%")
      (call-next-method))
    
    (defun test-dispatch ()
      (let ((x (make-instance 'bar))
            (y (make-instance 'bar)))
        (thing x y)))
    
    output:
    CL-USER> (test-dispatch)
    X is a BAR, Y is a FOO. Next...
    X is a FOO, Y is a BAR. Next...
    Both are of type FOO
    NIL

O aspecto-chave aqui, conforme eu descobri, é implementar a estratégia de prioridades entre as sobrecargas dos métodos de acordo com os tipos passados. Analisando bem por cima devemos sempre priorizar os métodos com os tipos mais específicos e ir realizando underpromotion até chegarmos no menos específico (se houver).

A implementação está no GitHub. Para o sistema de tipos em C nada como fazer do zero:

    /* defclass(foo, cclass_instance); */
    typedef struct foo_instance { cclass_instance type; } foo_instance;
    static foo_instance foo = { "foo" };
    
    /* defclass(bar, foo); */
    typedef struct bar_instance { cclass_instance type; } bar_instance; 
    static bar_instance bar = { "bar" };

As estruturas estão usando STL. O quê? Mas não era C? Sim, você tem toda razão. Porém, estou usando uma lib mais conhecida. Há milhares de libs containers em C para você escolher para trocar a implementação. Lembre-se que o mais importante não é ser purista, mas atingir os objetivos. Como eventualmente veremos nessa série de artigos, o próprio C++ e toda a sua biblioteca pode ser implementada em C. Este é apenas um atalho para fins didáticos e de produtividade (como eu já falei, produtividade não é o foco aqui, mas enxergar por debaixo dos panos).

Inicialmente feito em STL pela produtividade, a solução atual no GitHub é feita inteiramente em C usando a glib (lib comum em Linux com estrutura de dados, etc). O legal dessa biblioteca é que ela tem 20 anos (desde 1998) e já foi muito usada e testada, além de possuir estruturas e algoritmos simples que fazem parte do pacote básico de qualquer programador, como arrays, strings, hash tables.

    #include "cclos.h"
    #include <stdarg.h>
    #include <string.h>
    #include <gmodule.h>
    
    
    typedef GPtrArray Argv;
    
    typedef struct _Method
    {
    	void* fun;
    	Argv* argv;
    } Method;
    
    typedef void (*FP_Argv0)();
    typedef void (*FP_Argv1)(cclass_instance*);
    typedef void (*FP_Argv2)(cclass_instance*, cclass_instance*);
    typedef void (*FP_Argv3)(cclass_instance*, cclass_instance*, cclass_instance*);
    
    typedef GHashTable ClassMap;
    typedef GPtrArray Methods;
    typedef GHashTable MethodMap;
    
    static ClassMap* g_classes;
    static MethodMap* g_methods;
    static Methods* g_calledMethods;
    
    
    void cdefgeneric_initialize()
    {
    	g_classes = g_hash_table_new(g_str_hash, g_str_equal);
    	g_methods = g_hash_table_new(g_str_hash, g_str_equal);
    }
    
    
    Method* method_new(void* fun, Argv* argv)
    {
    	Method* ret = (Method*)malloc(sizeof(Method));
    	if (ret)
    	{
    		ret->fun = fun;
    		ret->argv = argv ? argv : g_ptr_array_new();
    	}
    	return ret;
    }
    
    Argv* method_free(Method* method, gboolean free_seg)
    {
    	Argv* ret = free_seg ? g_ptr_array_free(method->argv, TRUE), NULL : method->argv;
    	free(method);
    	return ret;
    }
    
    
    const char* defclass(const char* name, const char* deriv)
    {
    	gboolean insertOk = g_hash_table_insert(g_classes, (gpointer*)name, (gpointer*)deriv);
    	return name;
    }
    
    #define extractargv(argv, argc) \
    		va_list vl; \
    		va_start(vl, argc); \
    		for (int i = 0; i < argc; ++i) \
    		{ \
    			cclass_instance* arg = va_arg(vl, cclass_instance*); \
    			g_ptr_array_add(argv, arg); \
    		}
    
    void defmethod(const char* name, void* fun, int argc, ...)
    {
    	Method* method = method_new(fun, NULL);
    	Methods* methods = (Methods*)g_hash_table_lookup(g_methods, name);
    	extractargv(method->argv, argc);
    	if (!methods)
    	{
    		methods = g_ptr_array_new();
    		g_hash_table_insert(g_methods, (gpointer) name, (gpointer) methods);
    	}
    	g_ptr_array_add(methods, method);
    }
    
    void callmethod(const char* name, Method* method)
    {
    	g_ptr_array_add(g_calledMethods, (gpointer) method->fun);
    	cclass_instance** argv = (cclass_instance * *)method->argv->pdata;
    
    	if (method->argv->len == 0)
    	{
    		FP_Argv0 fun = (FP_Argv0)method->fun;
    		fun();
    	}
    	else if (method->argv->len == 1)
    	{
    		FP_Argv1 fun = (FP_Argv1)method->fun;
    		fun(argv[0]);
    	}
    	else if (method->argv->len == 2)
    	{
    		FP_Argv2 fun = (FP_Argv2)method->fun;
    		fun(argv[0], argv[1]);
    	}
    	else if (method->argv->len == 3)
    	{
    		FP_Argv3 fun = (FP_Argv3)method->fun;
    		fun(argv[0], argv[1], argv[2]);
    	}
    }
    
    Method* find_method_by_fun(const char* name, void* fun)
    {
    	Method* method = NULL;
    	Methods* methods = (Methods*) g_hash_table_lookup(g_methods, name);
    	if (methods)
    	{
    		Method** meths = (Method**)methods->pdata;
    		guint i = 0;
    		while (i < methods->len)
    		{
    			Method* m = meths[i];
    			if (m->fun == fun)
    			{
    				method = m;
    				break;
    			}
    			++i;
    		}
    	}
    	return method;
    }
    
    int calcdistance_arg(cclass_instance* arg, cclass_instance* underpromo)
    {
    	int ret = 0;
    	char* promo = (char*)arg->type;
    
    	while (strcmp(promo, underpromo->type) != 0)
    	{
    		promo = (char*)g_hash_table_lookup(g_classes, (gpointer*)promo);
    		if (!promo || strlen(promo) == 0)
    		{
    			ret = -1;
    			break;
    		}
    		++ret;
    	}
    
    	return ret;
    }
    
    int calcdistance(cclass_instance** args, cclass_instance** underpromo, int len)
    {
    	int ret = 0;
    	for (int i = 0; i < len; ++i)
    	{
    		int dist = calcdistance_arg(args[i], underpromo[i]);
    		if (dist == -1) return -1;
    		ret += dist;
    	}
    	return ret;
    }
    
    void call_next_method(const char* name, int argc, ...)
    {
    	Method* method = method_new(NULL, NULL);
    	extractargv(method->argv, argc);
    
    	int nextdist = 666;
    	Methods* methods = (Methods*)g_hash_table_lookup(g_methods, name);
    	if (methods)
    	{
    		guint i = 0;
    		while( i < methods->len )
    		{
    			Method* m = ((Method * *)methods->pdata)[i];
    			gboolean alreadyCalled = FALSE;
    			guint cms = 0;
    
    			while (cms < g_calledMethods->len)
    			{
    				void* fun = ((void **)g_calledMethods->pdata)[cms];
    				if (fun == m->fun)
    				{
    					alreadyCalled = TRUE;
    					break;
    				}
    				++cms;
    			}
    
    			if ( ! alreadyCalled)
    			{
    				int dist = -1;
    
    				if (method->argv->len == m->argv->len)
    					dist = calcdistance((cclass_instance * *)method->argv->pdata, (cclass_instance * *)m->argv->pdata, method->argv->len);
    
    				if (dist >= 0 && dist < nextdist)
    				{
    					if (dist < nextdist)
    					{
    						method->fun = m->fun;
    						nextdist = dist;
    					}
    				}
    			}
    
    			++i;
    		}
    
    		if (method->fun)
    			callmethod(name, method);
    	}
    }
    
    void call(const char* name, int argc, ...)
    {
    	g_calledMethods = g_ptr_array_new();
    
    	Method* method = method_new(NULL, NULL);
    	extractargv(method->argv, argc);
    
    	int nextdist = 666;
    	Methods* methods = g_hash_table_lookup(g_methods, name);
    	if (methods)
    	{
    		guint i = 0;
    		while( i < methods->len )
    		{
    			Method* m = ((Method * *)methods->pdata)[i];
    			int dist = -1;
    
    			if (method->argv->len == m->argv->len)
    				dist = calcdistance((cclass_instance * *)method->argv->pdata, (cclass_instance * *)m->argv->pdata, method->argv->len);
    
    			if (dist >= 0 && dist < nextdist)
    			{
    				if (dist < nextdist)
    				{
    					method->fun = m->fun;
    					nextdist = dist;
    				}
    			}
    
    			++i;
    		}
    
    		if (method->fun)
    			callmethod(name, method);
    	}
    
    	method_free(method, TRUE);
    }
    

O código é bem simples. Mapas e listas com strings e ponteiros para organizar as estruturas por detrás do sistema de tipos que estamos implementando e seus métodos sobrecarregados. Cada método possui um nome, um endereço de ponteiro e o número dos seus argumentos. Todos os argumentos são do tipo polimórfico, seguindo o que provavelmente existe por detrás da própria implementação do Lisp.

O código que utiliza a clos.c é bem direto e enxuto. Como no Lisp.

    #include "cclos.h"
    #include <stdio.h>
    
    /* defclass(foo, cclass_instance); */
    typedef struct foo_instance { cclass_instance type; } foo_instance;
    static foo_instance foo = { "foo" };
    
    /* defclass(bar, foo); */
    typedef struct bar_instance { cclass_instance type; } bar_instance; 
    static bar_instance bar = { "bar" };
    
    void test_dispatch()
    {
    	bar_instance x = bar;
    	bar_instance y = bar;
    	call("thing", 2, &x, &y);
    }
    
    void thing_foo_foo(cclass_instance* x, cclass_instance* y)
    {
    	printf("Both are of type FOO\n");
    }
    
    void thing_bar_foo(cclass_instance* x, cclass_instance* y)
    {
    	printf("X is BAR, Y is FOO. Next...\n");
    	call_next_method("thing", 2, x, y);
    }
    
    void thing_foo_bar(cclass_instance* x, cclass_instance* y)
    {
    	printf("X is FOO, Y is BAR. Next...\n");
    	call_next_method("thing", 2, x, y);
    }
    
    int main()
    {
    	cdefgeneric_initialize();
    	defclass("foo", "cclass");
    	defclass("bar", "foo");
    	defmethod("thing", &thing_foo_foo, 2, &foo, &foo);
    	defmethod("thing", &thing_bar_foo, 2, &bar, &foo);
    	defmethod("thing", &thing_foo_bar, 2, &foo, &bar);
    	test_dispatch();
    }

Futuros posts sobre C Resolve Tudo poderão utilizar a glib ou qualquer outra. Uma outra vantagem da linguagem C é que sua biblioteca padrão é muito enxuta, sendo fácil de ter disponível em seu ambiente um compilador C com a clib, e em cima dela você pode utilizar qualquer biblioteca de sua escolha para estruturas e algoritmos mais complexos. Ou fazer a sua própria.
