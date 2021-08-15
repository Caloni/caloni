---
categories:
- blog
date: 2019-04-29 20:03:18-03:00
tags:
title: OpenSSH no Windows
---

O Secure Shell (SSH) é um protocolo de sucesso nos unixes da vida para terminal remoto e seguro por décadas, mas no Windows nunca houve uma forma simples e protegida de abrir um terminal ou copiar arquivos. A opção é instalar um cygwin com esse componente ou tentar compilar um protocolo SSL e em cima dele o SSH. Porém, há detalhes na autenticação que estão relacionadas com o Sistema Operacional e que precisa ser feito. O OpenSSH é uma maneira de compilar tudo isso e ainda funcionar no Windows.

O software WinSCP, um client SFTP para Windows, possui [um guia](https://winscp.net/eng/docs/guide_windows_openssh_server) sobre como instalar essa opção no Windows. A partir do Windows Server 2019 e Windows 10 1809 isso não será mais necessário, pois já estará disponível entre as ferramentas opcionais instaláveis do SO (Apps > Apps & features > Manage optional features, "OpenSSH server"). Para os que ainda precisam manter o passado há uma maneira.

Se você preferir não compilar [a partir dos fontes](https://github.com/PowerShell/openssh-portable) você pode baixar um pacote dos [binários](https://github.com/PowerShell/Win32-OpenSSH/releases) pelo GitHub. Basta extrair tudo para uma pasta e rodar o script PowerShell de instalação e o serviço sshd estará instalado no modo manual (se você já usou o cygwin sabe que o nome é o mesmo). O local indicado para conter os arquivos é em `C:\Program Files\OpenSSH`, conforme [o tutorial do WinSCP](https://winscp.net/eng/docs/guide_windows_openssh_server).

![](https://i.imgur.com/7qdGAFB.png)

Após instalado você deve abrir a porta 22 pelo firewall do Windows (há uma maneira PowerShell de fazer se tiver um Windows novo ou usar a interface mesmo se tiver um antigo). Após esse último passo tudo deverá estar funcionando, e basta criar seu par de chaves pública/privada com o `ssh-keygen.exe` e adicionar no servidor com `ssh-add.exe`, além de copiar para um arquivo chamado `authorized_keys`... enfim, está tudo no tutorial.

Menos a parte de mudar o `sshd_config`.

Como nos informa [um post do Stack Overflow](https://stackoverflow.com/questions/16212816/setting-up-openssh-for-windows-using-public-key-authentication), é preciso comentar no arquivo `c:\programdata\ssh\ssh_config`, próximo do final, essas duas linhas:

```
Match Group administrators
       AuthorizedKeysFile __PROGRAMDATA__/ssh/administrators_authorized_keys
```

Para isso:

```
#Match Group administrators
#       AuthorizedKeysFile __PROGRAMDATA__/ssh/administrators_authorized_keys
```

Aí, sim. Reiniciar, o serviço e testar a conexão:

```
ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no domain\user@host
```

Os programas `ssh.exe` (shell remoto) e `scp.exe` (cópia remota de arquivos) também estão disponíveis no pacote OpenSSH, mas a versão do Cygwin ou até do Git (que vem com um pacote de ferramentas básicas de Linux) funcionam.

#### Serviço de cópia remota de arquivos

Se seu objetivo é realizar backups remotos silenciosos e para isso você instalar um serviço que irá executar o `scp.exe` de tempos em tempos é preciso tomar cuidado com as credenciais usadas e onde estarão as chaves de criptografia. O padrão usado pelo OpenSSH no Windows é na pasta `C:\Users\Usuário\.ssh`, mas para um processo na conta de sistema esse valor deve ser diferente. No caso de um terminal executando pelo `psexec.exe` ele ficou apontando para `c:\windows\system32\.ssh`, mas para serviços rodando como `SYSTEM` é capaz que seja outro valor. Enfim, é necessário testar e verificar os resultados dos testes.
