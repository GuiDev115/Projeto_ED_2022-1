# Projeto_ED_2022-1

Por ser muito grande o arquivo .csv que estamos trabalhando, ele está disponível aqui: https://drive.google.com/drive/folders/1WzGpaS9SNHUlrDSybl4WntzU7NMdYonE

Sendo o que foi escolhido: san_francisco_payroll_dataset.csv

O arquivo binário é igualmente grande para ser postado aqui, logo pode ser acessado pelo link: https://drive.google.com/file/d/1jb9453oBioO4gt9QGU5d7szspVFyrCSR/view?usp=sharing

Pontos importantes:

1) Por algum motivo, converter de .csv para .bin no windows dá errado, 
no linux eu consegui ir até certo ponto, mas dava errado o resto por uma implementação que ainda iria fazer

Resolvido: no windows tem que colocar o ios::binary ao criar o arquivo, para especificar que o arquivo deve ser escrito/lido em binário.
