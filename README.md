# Hotel ENSOF1BM3
Repositório compartilhado para a entrega de trabalho de sistema de hotel requerido pelo professor Hudson Neves para a aquisição de pontuação para o primeiro semestre do curso de Engenharia de Software da Uniceplac.

O seguinte projeto tem por objetivo fazer a entrega de um sistema utilizado por um hotel fictício, em que apresenta um módulo de hóspedes, um módulo de quartos, módulo de reservas, financeiro, módulo de serviços e relatório. O grupo se dividiu para criar o sistema que rodasse em terminal no **VS CODE**.

O projeto tem como base de aprendizado a lógica de programação, o desenvolvimento de linguagem, bem como conceitos básicos de variáveis, blocos de programas, funções, manipulação de dados, entre outros.

O projeto não requer banco de dados, nem uma linguagem de front-end, rodando tudo em terminal.

Os integrantes do grupo são:
- Daniel Costa Alves da Silva
- Gabriel Mendes Siqueira
- Guilherme Henrique Pessoa Mota
- Gustavo Braga Costa
- Ícaro Scárdua Del Medeiros e Silva
- João Henrique Gomes de Souza Alberto
- Josué Ribeiro Lenhardt
- Luigi Gomes de Oliveira
- Oto Pereira Bonfim
- Rodrigo Alves de Carvalho Souza
- Vitor Emanuel de Moura Soares Quirino


Professor orientador: Hudson Neves

***
## Como rodar o programa?
Primieramente tem-se que gerar um arquivo executável. Isso é feito colocando o código ```gcc (nome do arquivo).c -o hotel```

Isso irá gerar um arquivo executável com o nome "hotel". Em seguida execute o comando ```./hotel```

Assim, o programa rodará em seu terminal.

***
##O que o sistema pode fazer?

➡️Módulo de Hóspedes

    ✅Cadastro

    ✅Busca
  
    ✅Alteração
  
    ✅Exclusão



  
➡️Módulo de Quartos

    ✅Cadastro
  
    ✅Listagem
  
    ✅Busca
  
    ✅Alteração
  
    ✅Exclusão
  
    ✅Status do quarto



  
➡️Módulo de Reservas

    ✅Criar reserva
  
    ✅Cancelar reserva
  
    ✅Alterar reserva
  
    ✅Check-in
  
    ✅Check-out



  
➡️Módulo de Serviços
  
    ✅Café da manhã
  
    ✅Lavanderia
  
    ✅Transporte
  
    ✅Restaurante



  
➡️Financeiro

    ✅Calcular hospedagem
  
    ✅Registrar pagamento
  
    ✅Emitir recibo



  
➡️Relatórios

    ✅Quartos ocupados
  
    ✅Quartos livres
  
    ✅Reservas por período
  
    ✅Faturamento
 
    ✅Serviços mais utilizados

***
##Futuras melhorias e erros encontrados

Devido ao tempo disponível, nosso código ficou com muitos furos. Fizemos uso de IAs para basear nosso código e posteriormente limpar e melhorar o código. Um exemplo é o fato de a IA colocar a opção de ```buscarHospede()``` por meio do ID, nosso grupo encontrou a necessidade e viu que seria melhor a busca ser feita pelo CPF.

Não tivemos sucesso em integrar tudo no ```sistemaPrincipal.c```, pois ao tentar rodar, foi apresentado erro fatal. Ainda não conseguimos identificar a fragilidade.

Futuramente pretendemos melhorar o código, integra-lo a banco de dados, telas e fazer rodar bem o ```sistemaPrincipal.c```!
