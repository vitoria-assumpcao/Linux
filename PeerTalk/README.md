Sistema PeerTalk
O sistema PeerTalk também é um sistema para comunicação e troca de mensagens entre usuários com uma
funcionalidade similar ao sistema CentralTalk, porém o sistema PeerTalk opera de forma descentralizada
não tendo a necessidade de um processo central de controle como o processo servidor chairman do sistema
CentralTalk. Assim o único tipo de componente (processo) do sistema PeerTalk é o processo peertalker, que
interage com outros processos peertalker, usando mecanismos de comunicação peer-to-peer, para prover os
serviços de comunicação entre os usuários. A figura 4 mostra a arquitetura geral do sistema PeerTalk.

A comunicação entre estes processos peertalker é implementada pelos mecanismos de IPC vistos em aula,
necessitando das filas de mensagens, de memória compartilhada e de semáforos/mutexes para implementar corretamente o suporte para a comunicação entre os usuários.
Note que diferente do mecanismo de comunicação de rede utilizado na Internet (a interface socket), que segue os princípios da arquitetura cliente-servidor, os mecanismos de IPC de memória compartilhada e filas de
mensagens (e também os mecanismos de sincronismo de semáforos e mutexes) são essencialmente peerto-peer, não obrigando que os processos tenha que assumir o papel de clientes ou de servidores para poder
usar esses mecanismos. Em outras palavras, nada impede que um sistema que use os mecanismos de IPC
vistos em aula seja projetado como um sistema cliente-servidor (como o sistema CentralTalk sugerido como
outro projeto prático), mas nada obriga a usar apenas esse tipo de arquitetura de software para sistemas concorrente, outros tipos de arquitetura também podem ser facilmente explorados, como é o caso da arquitetura
peer-to-peer usado no sistema PeerTalk.
Para entrar no sistema PeerTalk um usuário deve abrir uma janela de terminal e executar o programa peertalker e se logar no sistema. No login o usuário deve informar seu nome de usuário (não é necessário senha),
que é um texto sem espaço em branco de até 20 caracteres.
A lista de usuários logados no sistema deve ser guardada em uma área de memória compartilhada por todos
os processos peertalker. Essa área é uma seção crítica do sistema PeerTalk, assim o acesso mutuamente
exclusivo a essa área deve ser garantido por meio de mutexes, para evitar que ocorram problemas e conflitos
no acesso e (principalmente) na alteração lista de usuários logados. Depois de conseguir acesso exclusivo
a lista de usuários logados o processo peertalker deve verificar se o usuário que está se logando já não
está presente no sistema. Se não houver nenhum outro usuário já logado com o mesmo nome, o login será
aceito. Neste caso o processo peertalker irá cadastrar o nome do usuário em conjunto com o PID (Process
IDentifier) do processo cliente peertalker que servirá como identificador único do usuário enquanto estiver
logado. Depois basta liberar o acesso exclusivo para essa lista.
Para troca de informações entre os processos peertalker que foram criados para cada usuário distinto logado
no sistema é utilizado uma fila de mensagens geral do sistema PeerTalk. O campo inicial da mensagem 7
contém o identificador ou código do tipo de mensagem (msgtyp) que é usado para separar as mensagens
destinadas a um particular processo peertalker. Este campo deve conter o PID do processo peertalker a
que se destina a mensagem. Logo após o campo inicial com PID do processo peertalker de destino, a
mensagem deve conter um campo com o PID do processo peertalker originador da mensagem. Depois
desses dois campos seguem os demais campos de dados da mensagem. Porém com esses dois campos
iniciais é possível estabelecer a comunicação peer-to-peer entre quaisquer dois processos peertalker.
Note que diferente do cliente speaker do sistema CentralTalk, o processo peertalker faz muito mais do que
apenas ler os comandos do usuário e verificar se estão corretamente digitados. O processo peertalker deve
efetivamente executar os comandos com base nas informações contidas nas áreas de memória e nas filas de
mensagens compartilhadas entre todos os processos do sistema PeerTalk.
Os comandos de usuário tratados pelos processos peertalker, são os seguintes:
• send <nome-usuário>, <texto-mensagem> – envia uma mensagem direta do usuário atual para o usuário destino identificado por <nome-usuário>. Primeiro o processo peertalker deve consultar a lista de
usuários logados e verificar se o usuário <nome-usuário> existe. Em caso afirmativo, então uma mensagem contendo <texto-mensagem> e o PID desse usuário (que foi extraído da lista de usuários) deve
ser enviada para a fila de mensagens geral do sistema. A mensagem somente é enviada se o usuário
estiver logado no sistema, caso contrário uma mensagem de erro deve ser mostrada na tela.
• recv – retira da fila de mensagens do sistema, todas as mensagens que tem o PID igual ao PID do
usuário corrente e guarda essas mensagens no fim da tabela local de mensagens que já foram recebidas
pelo usuário. Se não houver nenhuma mensagem destinada ao usuário avisa que não há mensagens
recebidas.
• msgs – mostra na tela todas as mensagens que estão na tabela local de mensagens. Se não houver
nenhuma mensagem na tabela local, avisa que não há mensagens armazenadas.
• del msgs – remove (deleta) todas as mensagens destinadas ao usuário. No caso apenas deleta a
copia local das mensagens que foram enviadas para o usuário, mensagens que ainda estejam na fila de
mensagens geral do sistema são deixadas lá e não são excluídas.
• users – mostra na tela a lista de usuários logados no sistema. A lista de usuários é mantida como uma
estrutura de dados em uma área de memória compartilhada formando uma área crítica. Assim o acesso
a essa lista deve ser feito somente através de mutexes.
• myid – mostra o identificador do usuário atual.
• exit – sai do sistema PeerTalk, mas antes desloga o usuário, ou seja, descadastra o usuário da lista de
usuários logados.
