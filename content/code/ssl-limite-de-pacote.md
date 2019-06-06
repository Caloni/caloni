---
date: 2018-05-22T15:16:14-03:00
title: "SSL e seu limite de pacote"
categories: [ "code" ]
---
O protocolo TLS/SSL tem por objetivo criar uma camada de criptografia assimétrica para a aplicação. E quando eu falo em camada não estou me referindo às camadas OSI. Nem às camadas TCP/IP. Isso porque o SSL **não se encaixa** em nenhuma das duas. Ele interfere com muitas, inclusive a aplicação. E aprendi isso a duras penas: na ponta do depurador.

O pacote SSL tem um limite de 16 KB, ou 16384 bytes. Esse é o limite que será respeitado por qualquer implementação do protocolo, o que inclui o uso de [Boost.Asio](https://www.boost.org/doc/libs/1_66_0/doc/html/boost_asio.html) e seu uso da [OpenSSL](https://www.openssl.org/). O que isso quer dizer na teoria é que você não pode trafegar sentido server=>client nada maior que 16k bytes. O que isso quer dizer na prática é que sua aplicação não pode escrever mais que 16k bytes de uma vez no socket que vai dar pau.

Sim, a camada de aplicação tem que estar ligada que existe SSL abaixo dela.

Isso quer dizer que este snippet de código, por exemplo:

```
_sock.write_some(::boost::asio::buffer(output.data(), output.size()), err);
```

Não é inocente e não funciona sempre. Se _sock for um socket cuja comunicação está encriptada por SSL (em outras palavras -- em Boostês -- ele for um ssl_socket) você **precisa** escrever output em pequenas quantidades. Como em outra implementação inocente:

```
do
{
    size_t sz = std::min((size_t) LESS_THAN_16_KB, output.size());
    _sock.write_some(::boost::asio::buffer(output.data(), sz), err);
    output.erase(0, sz);
}
while (err.value() == boost::system::errc::success && output.size() > 0 );
```

Se isso não for feito e a ponta server escrever, digamos, 512KB, ou 17KB, ou qualquer coisa acima de 16KB, ela irá receber... 16 KB. E acabou. O resto se perder.

Portanto, quando for mexer com SSL, esqueça OSI e esqueça TCP/IP. As coisas funcionam de uma maneira muito mais esotérica que qualquer programador de redes jamais viu, e jamais verá.
