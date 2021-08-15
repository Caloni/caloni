---
categories:
- code
date: 2018-05-21 00:23:49-03:00
tags:
title: Boost Meta State Machine
---

O Boost Meta State Machine (MSM for short) é uma das duas bibliotecas mais famosinhas de state machine do Boost. Ela é uma versão estática que permite incluir chamadas para as entradas e saídas de um estado baseado em eventos. A sua principal vantagem é poder visualizar toda a máquina de estado em um só lugar, e sua principal desvantagem é pertecer ao Boost, o que quer dizer que você vai precisar fazer seu terceiro doutorado e ler uma documentação imensa sobre UML antes de conseguir produzir alguma coisa. Ou ler este artigo de 10 minutos tops.

```
#include <iostream>

#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/functor_row.hpp>

using namespace std;

namespace MyStateMachine
{
    namespace msm = boost::msm;
    namespace msmf = boost::msm::front;
    namespace mpl = boost::mpl;

    namespace Events
    {
        struct Event1 {};
        struct Event2 { int data; };
        struct Event3 {};
    }

    struct StateMachine :msmf::state_machine_def<StateMachine>
    {
        typedef msm::back::state_machine<StateMachine> SM;

        struct Off :msmf::terminate_state<> // Off is the last state
        {
            template <class Event, class Fsm>
            void on_entry(Event const&, Fsm&) const
            {
                cout << "on_entry Off generic event\n";
            }
        }; 

        struct On :msmf::state<>
        {
            template <class Event, class Fsm>
            void on_entry(Event const&, Fsm&) const
            {
                cout << "on_entry On generic event\n";
            }

            template <class Fsm>
            void on_entry(Events::Event1 const&, Fsm&) const
            {
                cout << "on_entry On Event1\n";
            }

            template <class Event, class Fsm>
            void on_exit(Event const&, Fsm&) const
            {
                cout << "on_exit On generic event\n";
            }

            template <class Fsm>
            void on_exit(Events::Event2 const& evt, Fsm&) const
            {
                cout << "on_exit On Event2 (with data " << evt.data << ")\n";
            }
        };

        struct Tick :msmf::state<>
        {
            template <class Event, class Fsm>
            void on_entry(Event const&, Fsm&) const
            {
                cout << "on_entry Tick generic event\n";
            }

            template <class Fsm>
            void on_entry(Events::Event3 const&, Fsm&) const
            {
                cout << "on_entry Tick Event3\n";
            }

            template <class Event, class Fsm>
            void on_exit(Event const&, Fsm&) const
            {
                cout << "on_exit Tick generic event\n";
            }
        };

        typedef On initial_state; // On is the start

        struct transition_table :mpl::vector<
            //          Start      Event                     Next               Action                      Guard
            msmf::Row < On,        Events::Event1,           On,                msmf::none, msmf::none >,
            msmf::Row < On,        Events::Event2,           Tick,              msmf::none, msmf::none >,
            msmf::Row < Tick,      Events::Event3,           Tick,              msmf::none, msmf::none >,
            msmf::Row < Tick,      Events::Event1,           On,                msmf::none, msmf::none >,
            msmf::Row < Tick,      Events::Event2,           Off,               msmf::none, msmf::none >
        > {};
    };

    int TestPathway()
    {
        StateMachine::SM sm1;
        sm1.start();
        sm1.process_event(Events::Event1()); // keep in On
        sm1.process_event(Events::Event2()); // to Tick
        sm1.process_event(Events::Event3()); // keep in Tick
        sm1.process_event(Events::Event1()); // back to On
        sm1.process_event(Events::Event2 { 42 }); // back to Tick
        sm1.process_event(Events::Event2()); // finish
        return 0;
    }
}

int main()
{
    MyStateMachine::TestPathway();
}
```

A parte bonitinha de se ver é os eventos e estados completamente ordenados:

```
struct transition_table :mpl::vector<
    //          Start      Event                     Next               Action                      Guard
    msmf::Row < On,        Events::Event1,           On,                msmf::none, msmf::none >,
    msmf::Row < On,        Events::Event2,           Tick,              msmf::none, msmf::none >,
    msmf::Row < Tick,      Events::Event3,           Tick,              msmf::none, msmf::none >,
    msmf::Row < Tick,      Events::Event1,           On,                msmf::none, msmf::none >,
    msmf::Row < Tick,      Events::Event2,           Off,               msmf::none, msmf::none >
> {};
```

Claro que a indentação ajuda. Para cada entrada e saída de um estado é possível utilizar os métodos on_entry e on_exit de cada struct que define um estado, seja este método um template totalmente genérico ou especificado por evento (e cada evento também é um struct, com direito a dados específicos).

```
template <class Event, class Fsm>
void on_entry(Event const&, Fsm&) const
{
    cout << "on_entry On generic event\n";
}

template <class Fsm>
void on_entry(Events::Event1 const&, Fsm&) const
{
    cout << "on_entry On Event1\n";
}

template <class Event, class Fsm>
void on_exit(Event const&, Fsm&) const
{
    cout << "on_exit On generic event\n";
}

template <class Fsm>
void on_exit(Events::Event2 const& evt, Fsm&) const
{
    cout << "on_exit On Event2 (with data " << evt.data << ")\n";
}
```

Quando é criada uma nova máquina de estados o estado inicial é chamado pelo evento on_entry genérico. Como sabemos qual é o estado inicial? Isso é definido pelo typedef initial_state dentro da classe da máquina de estado (que deve herdar de state_machine_def no estilo WTL, com sobrecarga estática):

```
struct StateMachine :msmf::state_machine_def<StateMachine>
//...
typedef On initial_state; // On is the start
```

O estado final também é definido, mas por herança. O estado final, que também é uma struct, deve herdar de terminate_state:

```
struct Off :msmf::terminate_state<>
```

A partir daí o método process_event serve para enviar eventos à máquina de estado que irá alterar seu estado dependendo do fluxo criado no nome transition_table dentro da máquina de estado (a tabelinha que vimos acima). A partir daí tudo é possível; a máquina de estado está à solta:

```
int TestPathway()
{
    StateMachine::SM sm1;
    sm1.start();
    sm1.process_event(Events::Event1()); // keep in On
    sm1.process_event(Events::Event2()); // to Tick
    sm1.process_event(Events::Event3()); // keep in Tick
    sm1.process_event(Events::Event1()); // back to On
    sm1.process_event(Events::Event2 { 42 }); // back to Tick
    sm1.process_event(Events::Event2()); // finish
    return 0;
}
```

Mas nesse exemplo didático está comportada em uma função apenas. Claro que cada método recebe a própria máquina de estado para ter a chance de alterá-la, ou guardá-la para uso futuro. Ela é recebida como parâmetro assim como o evento. E o evento, por ser uma struct também, pode conter outros dados relevantes para a transição.
