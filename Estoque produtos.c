#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h> //alocação de texto por região 

#define mx_users 10 // máximo de 10 usuários
#define mx_cads_prod 100 // Define the maximum number of prod_cad


// cadastro de produtos -------------------------------------------------------------------------------------------------------------------------
// Estrutura para armazenar os dados do cadastro
typedef struct { //funciona
  int id;
  char nome_pro[50];
  char std[50];
  char sit[50];
  char desc[100];
  char data[10];
  char pes[50];
} Cadastro;

Cadastro prod_cad[mx_cads_prod]; // Array da estrutura Cadastro 
int qntcad = 0; // contador de prod_cad

// Protótipos das funções
void cad_prod(Cadastro *prod_cad, int *qntcad);
void consul_prod(Cadastro *prod_cad, int qntcad);
void empr_prod(Cadastro *prod_cad, int qntcad);
void manu_prod(Cadastro *prod_cad, int qntcad);
void apagar_prod(Cadastro *prod_cad, int *qntcad);
void show_prod(Cadastro *prod_cad, int qntcad);
void show_prod_disponivel(Cadastro *prod_cad, int qntcad);
void show_prod_emprestado(Cadastro *prod_cad, int qntcad);
void show_prod_manu(Cadastro *prod_cad, int qntcad);

// Função para cadastrar um novo produto
void cad_prod(Cadastro *prod_cad, int *qntcad) { //funciona
	int situacao, estado, i;
    if (*qntcad < mx_cads_prod) {
        int novo_id, id_existe;
        
        // Loop para garantir que o ID seja único
        do {
            id_existe = 0; // Resetar o flag para verificar ID existente
            
            do {//valida se o número tem 11 digitos
        		printf("Digite o ID do produto: ");
        		scanf("%d", &novo_id);

		        if (novo_id<=0) {
		            printf("O id é inválido. O número deve ser maior que 0.\n");
		        }
		    }while (novo_id<=0);

            // Verifica se o ID já existe
            for (i = 0; i < *qntcad; i++) {
                if (prod_cad[i].id == novo_id) {
                    id_existe = 1; // ID encontrado, solicitar um novo
                    printf("Erro: O ID %d já está em uso. Por favor, insira outro.\n", novo_id);
                    break;
                }
            }
        } while (id_existe); // Repete até que o ID seja único

        // Se o ID for único, prosseguir com o cadastro
        prod_cad[*qntcad].id = novo_id;

        printf("Digite o nome do produto: ");
        scanf(" %[^\n]s", prod_cad[*qntcad].nome_pro);

		// Leitura e validação do estado do produto
        do {
            printf("Digite o estado do produto (usado = 0, novo = 1, defeituoso = 2, baixado = 3): ");
            scanf("%d", &estado);

            if (estado != 0 && estado != 1 && estado != 2 && estado != 3) {
                printf("Erro: Estado inválido. Por favor, insira 0 para velho ou 1 para novo.\n");
            }
        } while (estado != 0 && estado != 1 && estado != 2 && estado != 3);
        // Define o estado com base no valor inserido
        if (estado == 0) {
            strcpy(prod_cad[*qntcad].std, "usado");
        }else if (estado == 1) {
            strcpy(prod_cad[*qntcad].std, "novo");
        } else if (estado == 2) {
            strcpy(prod_cad[*qntcad].std, "defeituoso");
        } else {
            strcpy(prod_cad[*qntcad].std, "baixado");
        }

         // Loop para garantir que a situação do produto seja válida ("Disponível" = 0 ou "Manutenção" = 1)
        do {
            printf("Digite a situação do produto (Disponível = 0, Mnutenção = 1): ");
            scanf("%d", &situacao);

            if (situacao != 0 && situacao != 1) {
                printf("Erro: Situação inválida. Por favor, insira 1 para Disponível ou 0 para Emprestado.\n");
            }
        } while (situacao != 0 && situacao != 1);

        // Define a situação com base no valor inserido
        if (situacao == 0) {
            strcpy(prod_cad[*qntcad].sit, "Disponível");
        } else {
            strcpy(prod_cad[*qntcad].sit, "Manutenção");
        }

        printf("Digite a descrição do produto: ");
        scanf(" %[^\n]s", prod_cad[*qntcad].desc);

        printf("Cadastro realizado com sucesso!\n");
        (*qntcad)++;
        system("pause");
    } else {
        printf("Limite de cadastros alcançado.\n");
        system("pause");
    }
}

// Função para consultar um produto pelo ID
void consul_prod(Cadastro *prod_cad, int qntcad) { //funciona
    int id, i;
    printf("Digite o ID do produto que deseja consultar: ");
    scanf("%d", &id);

    for (i = 0; i < qntcad; i++) {
        if (prod_cad[i].id == id) {
            printf("ID: %d\n", prod_cad[i].id);
            printf("Nome: %s\n", prod_cad[i].nome_pro);
            printf("Estado: %s\n", prod_cad[i].std);
            printf("Situação: %s\n", prod_cad[i].sit);
            printf("Descrição: %s\n", prod_cad[i].desc);
            system("pause");
			return;
        }
    }
    printf("Produto não encontrado.\n");
    system("pause");
}

// Função para marcar produto como emprestado ou devolvido
void empr_prod(Cadastro *prod_cad, int qntcad) { //funciona
    int opcao, id, i;
    char pessoa[50], data_emprestimo[11];
    int produto_encontrado = 0; // Flag para verificar se o produto foi encontrado

    printf("Selecione uma opção:\n");
    printf("1 - Emprestar produto\n");
    printf("2 - Devolver produto\n");
    printf("Opção: ");
    scanf("%d", &opcao);
    getchar(); // Consumir o caractere de nova linha restante

    printf("Digite o ID do produto: ");
    scanf("%d", &id);
    getchar(); // Consumir o caractere de nova linha restante

    for (i = 0; i < qntcad; i++) {
        if (prod_cad[i].id == id) {
            produto_encontrado = 1; // Produto encontrado

            if (opcao == 1) {
                if (strcmp(prod_cad[i].sit, "Disponível") == 0) {
                    printf("Digite o nome da pessoa para quem o produto será emprestado: ");
                    fgets(pessoa, sizeof(pessoa), stdin);
                    pessoa[strcspn(pessoa, "\n")] = '\0'; // Remove a nova linha no final

                    printf("Digite a data do empréstimo (DD/MM/AAAA): ");
                    fgets(data_emprestimo, sizeof(data_emprestimo), stdin);
                    data_emprestimo[strcspn(data_emprestimo, "\n")] = '\0'; // Remove a nova linha no final

                    strcpy(prod_cad[i].sit, "Emprestado");
                    strcpy(prod_cad[i].pes, pessoa);
                    strcpy(prod_cad[i].data, data_emprestimo);
                    printf("Produto %d marcado como emprestado a %s em %s.\n", id, pessoa, data_emprestimo);
                } else {
                    printf("Produto %d não está disponível.\n", id);
                }
            } else if (opcao == 2) {
                if (strcmp(prod_cad[i].sit, "Emprestado") == 0) {
                    strcpy(prod_cad[i].sit, "Disponível");
                    strcpy(prod_cad[i].pes, ""); // Limpa o nome da pessoa
                    strcpy(prod_cad[i].data, ""); // Limpa a data
                    printf("Produto %d devolvido com sucesso!\n", id);
                } else {
                    printf("Produto %d não está emprestado.\n", id);
                }
            }
            break; // Encerra o laço após encontrar o produto
        }
    }

    if (!produto_encontrado) {
        printf("Produto não encontrado.\n");
    }
    system("pause");
}

void manu_prod(Cadastro *prod_cad, int qntcad) { //funciona
    int opcao, id, i;
    char pessoa[50], data_emprestimo[11];
    int produto_encontrado = 0; // Flag para verificar se o produto foi encontrado

    printf("Selecione uma opção:\n");
    printf("\t1) - Enviar produto para manutenção\n");
    printf("\t2) - Tirar produto da manutenção\n");
    printf("Opção: ");
    scanf("%d", &opcao);
    getchar(); // Consumir o caractere de nova linha restante

    printf("Digite o ID do produto: ");
    scanf("%d", &id);
    getchar(); // Consumir o caractere de nova linha restante

    for (i = 0; i < qntcad; i++) {
        if (prod_cad[i].id == id) {
            produto_encontrado = 1; // Produto encontrado

            if (opcao == 1) {
                if (strcmp(prod_cad[i].sit, "Disponível") == 0) {

                    strcpy(prod_cad[i].sit, "Manutenção");
                    printf("Produto %d foi para a manutenção\n", id);
                } else {
                    printf("Produto %d não está disponível para ser enviado para a manutenção.\n", id);
                }
            } else if (opcao == 2) {
                if (strcmp(prod_cad[i].sit, "Manutenção") == 0) {
                    strcpy(prod_cad[i].sit, "Disponível");
                    printf("Produto %d devolvido com sucesso!\n", id);
                } else {
                    printf("Produto %d não está na manutenção.\n", id);
                }
            }
            break; // Encerra o laço após encontrar o produto
        }
    }

    if (!produto_encontrado) {
        printf("Produto não encontrado.\n");
    }
    system("pause");
}

// Função para apagar um produto pelo ID
void apagar_prod(Cadastro *prod_cad, int *qntcad) { //funciona
    int id, i, j;  // Adicionada a variável 'j' para reorganizar o array
    printf("Digite o ID do produto que deseja apagar: ");
    scanf("%d", &id);

    for (i = 0; i < *qntcad; i++) {
        if (prod_cad[i].id == id) {
            // Reorganiza o array, removendo o produto
            for (j = i; j < *qntcad - 1; j++) {  // Novo: reorganiza para evitar buracos no array
                prod_cad[j] = prod_cad[j + 1];  // Move os produtos seguintes uma posição à esquerda
            }
            (*qntcad)--;  // Diminui o número total de produtos
            printf("Produto apagado com sucesso!\n");
            system("pause");
            return;
        }
    }
    printf("Produto não encontrado.\n");
    system("pause");
}

// Função para exibir as possivei listas
int lista_prod(){ //funciona
	int option;
	
	do{//loop usando while ao invez de for
    	system("cls");
    
	    printf("\tEscolha qual lista deseja ver: \n");
	    printf("Escolha a opção do menu:\n\n");
	    printf("\t 1) - Lista completa\n");
	    printf("\t 2) - Lista de produtos Emprestados\n");
		printf("\t 3) - Lista de produtos Disponíveis\n");
		printf("\t 4) - Lista de produtos em Manutenção\n");
	    printf("\t 5) - Sair\n");
	    printf("Opção: "); //Fim do menu
	
	    scanf("%d", &option); //Armazenar escolha
	
	    system("cls");
	
	    switch (option) {
	    	case 1:
	        	show_prod(prod_cad, qntcad);
	        break;
	    	case 2:
	        	show_prod_emprestado(prod_cad, qntcad);// funciona
	        break;
	        case 3:
	        	show_prod_disponivel(prod_cad, qntcad);// funciona
	        break;
	        case 4:
	        	show_prod_manu(prod_cad, qntcad);// funciona
	        break;
	    	case 5:
	        	return;
	        break;
	    	default:
	        	printf("Opção inválida.\n");
	    	break;
	    }
	} while (option != 7);
    system("pause");
}

// Função para exibir todos os produtos cadastrados
void show_prod(Cadastro *prod_cad, int qntcad) { //funciona
	
	if (qntcad == 0) {
		printf("Nenhum produto cadastrado.\n");
		system("pause");
		return;
	}
	int i;
	for (i = 0; i < qntcad; i++) {
		printf("ID: %d\n", prod_cad[i].id);
		printf("Nome: %s\n", prod_cad[i].nome_pro);
		printf("Estado: %s\n", prod_cad[i].std);
		printf("Situação: %s\n", prod_cad[i].sit);
		printf("Descrição: %s\n", prod_cad[i].desc);
		
		if (strcmp(prod_cad[i].sit, "Emprestado") == 0) {
			printf("Emprestado para: %s\n", prod_cad[i].pes);
			printf("Data: %s\n", prod_cad[i].data);
		}
		printf("----------------------------\n");
	}
	system("pause");
}

// Função para exibir todos os produtos cadastrados
void show_prod_disponivel(Cadastro *prod_cad, int qntcad) { //funciona
    if (qntcad == 0) {
        printf("Nenhum produto cadastrado.\n");
        system("pause");
        return;
    }
	printf("\tProdutos disponíveis: \n");
    int i;
    for (i = 0; i < qntcad; i++) {
        if (strcmp(prod_cad[i].sit, "Disponível") == 0) {
            printf("ID: %d\n", prod_cad[i].id);
	        printf("Nome: %s\n", prod_cad[i].nome_pro);
	        printf("Estado: %s\n", prod_cad[i].std);
	        printf("Descrição: %s\n", prod_cad[i].desc);
        }
		printf("----------------------------\n");
    }
    system("pause");
}

// Função para exibir todos os produtos cadastrados
void show_prod_emprestado(Cadastro *prod_cad, int qntcad) { //funciona
    if (qntcad == 0) {
        printf("Nenhum produto cadastrado.\n");
        system("pause");
        return;
    }
	printf("\tProdutos emprestados: \n");
    int i;
    for (i = 0; i < qntcad; i++) {
        if (strcmp(prod_cad[i].sit, "Emprestado") == 0) {
        	printf("ID: %d\n", prod_cad[i].id);
        	printf("Nome: %s\n", prod_cad[i].nome_pro);
        	printf("Estado: %s\n", prod_cad[i].std);
        	printf("Emprestado para: %s\n", prod_cad[i].pes);
			printf("Data: %s\n", prod_cad[i].data);
        	printf("Descrição: %s\n", prod_cad[i].desc);
        }
		printf("----------------------------\n");
    }
    system("pause");
}

// Função para exibir todos os produtos cadastrados
void show_prod_manu(Cadastro *prod_cad, int qntcad) { //funciona
    if (qntcad == 0) {
        printf("Nenhum produto cadastrado.\n");
        system("pause");
        return;
    }
	printf("\tProdutos em manutenção: \n");
    int i;
    for (i = 0; i < qntcad; i++) {
    	if(strcmp(prod_cad[i].sit, "Manutenção") == 0){
    		printf("ID: %d\n", prod_cad[i].id);
        	printf("Nome: %s\n", prod_cad[i].nome_pro);
        	printf("Estado: %s\n", prod_cad[i].std);
        	printf("Descrição: %s\n", prod_cad[i].desc);
			printf("----------------------------\n");
		}
    }
    system("pause");
}

//cadastro usuário ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Estrutura para armazenar os dados do cadastro de usuários
typedef struct {
    char nome[250];
    char cpf[12];
    char tel[40];
    char gmail[40];
    char pass[250];
} user;

user users[mx_users]; // vetor de structs para armazenar os usuários
int nm_users = 0; // contador de usuários cadastrados
int i; // inicia as variaveis para "for"
int j; // inicia as variaveis para "for"

// Funçoes para validação +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int cpf_cad(char *cpf) { //funciona
	int i;
    for (i = 0; i < nm_users; i++) {
        if (strcmp(users[i].cpf, cpf) == 0) {
            return 1; // CPF já está cadastrado
        }
    }
    return 0; // CPF não está cadastrado
}

int validar_cpf(char *cpf) { //funciona
    // Verificar se o CPF tem exatamente 11 dígitos e se todos são números
    if (strcmp(cpf, "chefe") == 0) {
        return 1;
	}else if (strlen(cpf) != 11) {
        return 0; // CPF inválido
    	
    	for (i = 0; i < 11; i++) {
        	if (!isdigit(cpf[i])) {
            	return 0; // Se algum caractere não for um dígito, retorna inválido
        	}
    	}
    }
    return 1; // CPF válido
}

int validar_tel(char *tel) { //funciona
    // Verificar se o tel tem exatamente 11 dígitos e se todos são números
    if (strlen(tel) != 11) {
        return 0; // tel inválido
    }

    for (i = 0; i < 11; i++) {
        if (!isdigit(tel[i])) {
            return 0; // Se algum caractere não for um dígito, retorna inválido
        }
    }
    return 1; // tel válido
}

int validar_pass(char *pass) { //funciona
    // Verificar se a senha tem exatamente 11 dígitos e se todos são números
    if (strcmp(pass, "adm") == 0) {
        return 1;
	}else if (strlen(pass) < 8) {
        return 0; // senha inválido
    }
    return 1; // senha válido
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

int cadast() { //Função cadastro concluida 
    setlocale(LC_ALL, "Portuguese"); 

    if (nm_users >= mx_users) { //se cadastrar mais que 10 usuários o cadastro para de funcionar 
        printf("Limite de usuários alcançado!\n");
        system("pause");
        return 0;
    }

    printf("\tCadastro\n\n"); //Tela de login
    printf("Nome: ");
    scanf("%s", users[nm_users].nome);
     while (1) {//valida o cpf
        printf("Digite o CPF (somente números, 11 dígitos): ");
        scanf("%s", users[nm_users].cpf);

        if (validar_cpf(users[nm_users].cpf)) {
            break; // CPF é válido, sai do laço
        } else {
            printf("CPF inválido. O CPF deve conter 11 dígitos numéricos.\n");
        }
    }
    
    // Verificar se o CPF já está cadastrado
    if (cpf_cad(users[nm_users].cpf)) {
        printf("CPF já está cadastrado!\n");
        system("pause");
        return 0;
    }
    
    while (1) {//valida se o número tem 11 digitos
        printf("Digite o telefone: ");
        scanf("%s", users[nm_users].tel);

        if (validar_tel(users[nm_users].tel)) {
            break; // tel é válido, sai do laço
        } else {
            printf("O telefone informado é inválido. O número deve conter 11 dígitos numéricos.\n");
        }
    }
    printf("Gmail: ");
    scanf("%s", users[nm_users].gmail);
    
    while (1) {//valida se a senha tem mais de 8 caracteres
        printf("Senha: ");
        scanf("%s", users[nm_users].pass);

        if (validar_pass(users[nm_users].pass)) {
            break; // senha é válido, sai do laço
        } else {
            printf("A senha deve conter no mínimo 8 dígitos.\n");
        }
    }
    
    //colocar uma mensagem caso o cpf ja esteja cadastrado

    nm_users++; // incrementa o contador de usuários
    printf("Usuário cadastrado com sucesso!\n");

    system("pause");
    return 0; // volta pra tela inicial 
}

int login() { //Funcao login concluida
    setlocale(LC_ALL, "Portuguese"); //Definindo linguagem

    char cpf[12];
    char pass[250];
    int i;

    printf("Login\n\n");
    while (1) {
        printf("Digite o CPF (somente números, 11 dígitos): ");
        scanf("%s", cpf);

        if (validar_cpf(cpf)) {
            break; // CPF é válido, sai do laço
        } else {
            printf("CPF inválido. O CPF deve conter 11 dígitos numéricos.\n");
        }
    }
    
    while (1) {
        printf("Senha: ");
        scanf("%s", pass);

        if (validar_pass(pass)) {
            break; // senha é válido, sai do laço
        } else {
            printf("A senha deve conter no mínimo 8 dígitos.\n");
        }
    }

    if ((strcmp(cpf, "chefe") == 0) && (strcmp(pass, "adm") == 0)) {
        boss(); // Chama a função do administrador
    } else {
        for (i = 0; i < nm_users; i++) {
            if (strcmp(users[i].cpf, cpf) == 0 && strcmp(users[i].pass, pass) == 0) {
                printf("Login realizado com sucesso!\n");
                system("pause");
                usua(); // Chama a função para o usuário normal
                return 0;
            }
        }
        printf("CPF ou senha incorretos!\n");
    }
    system("pause");
    return 1;
}

//utilidades do adm++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int del() { //funciona 
    setlocale(LC_ALL, "Portuguese"); //Definindo linguagem

    char cpf[12];

    
     while (1) {
        printf("Digite o CPF (somente números, 11 dígitos): ");
        scanf("%s", cpf);

        if (validar_cpf(cpf)) {
            break; // CPF é válido, sai do laço
        } else {
            printf("CPF inválido. O CPF deve conter 11 dígitos numéricos.\n");
        }
    }

    // Procurar pelo CPF na lista de usuários
    for (i = 0; i < nm_users; i++) {
        if (strcmp(users[i].cpf, cpf) == 0) { // Comparar CPF informado com o CPF dos usuários
            // Encontrou o usuário, agora remover da lista
            for (j = i; j < nm_users - 1; j++) {
                users[j] = users[j + 1]; // Desloca os usuários subsequentes
            }
            nm_users--; // Decrementa o número de usuários após a exclusão
            printf("Usuário deletado com sucesso!\n");
            system("pause");
            return 0;
        }
    }

    // Caso o CPF não seja encontrado
    printf("CPF não encontrado...\n");
    system("pause");
    return 1;
}

void show_user(user *users, int nm_users) { //concluida
	int i;
    for (i = 0; i < nm_users; i++) {
        printf("Usuário %d:\n", i + 1);
        printf("Nome: %s\n", users[i].nome);
        printf("CPF: %s\n", users[i].cpf);
        printf("Telefone: %s\n", users[i].tel);
        printf("Gmail: %s\n", users[i].gmail);
        printf("\n");
    }
    system("pause");
}

void consult_user() { //concluida
    setlocale(LC_ALL, "Portuguese"); // Definindo linguagem

    char cpf[12];
    int encontrado = 0; // Flag para verificar se algum usuário foi encontrado

    while (1) {
        printf("Digite o cpf do usuário que deseja consultar: ");
        scanf("%s", cpf);

        if (validar_cpf(cpf)) {
            break; // CPF é válido, sai do laço
        } else {
            printf("CPF inválido. O CPF deve conter 11 dígitos numéricos.\n");
        }
    }

    for (i = 0; i < nm_users; i++) {
        // Comparar o nome informado com o nome dos usuários (sem diferenciação de maiúsculas/minúsculas)
        if (strcasecmp(users[i].cpf, cpf) == 0) {
            printf("\nUsuário encontrado:\n");
            printf("Nome: %s\n", users[i].nome);
            printf("CPF: %s\n", users[i].cpf);
            printf("Telefone: %s\n", users[i].tel);
            printf("Gmail: %s\n", users[i].gmail);
            printf("-------------------------------\n");
            encontrado = 1; // Marca que encontrou o usuário
        }
    }

    if (!encontrado) {
        printf("Usuário não encontrado com o nome informado.\n");
    }

    system("pause");
}

//tela principal ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int main() {
    setlocale(LC_ALL, "Portuguese"); //Definindo linguagem

    int option = 0; //Definindo a variavel
    int laco = 1;

    for (laco = 1; laco = 1;) {
        system("cls");
        
        if (nm_users >= mx_users) { //se cadastrar mais que 10 usuários o cadastro some da tela incial 
	        printf(".... Tela inicial ....\n\n"); //Inicio do menu
	        printf("Escolha a opção do menu:\n\n");
	        printf("\t 1) - Login\n");
	        printf("\t 2) - Sair\n");
	        printf("Opção: "); //Fim do menu
	
	        scanf("%d", &option); //Armazenar escolha
	
	        system("cls");
	
	        switch (option) { //Inicio da seleção
		        case 1:
		            login();
		            break;
				case 2:
		        	printf("Saindo...");
		        	return 0;
		        break;
		        default:
		            printf("Opção Invalida\n");
		            system("pause");
		            break;
	        } //fim da seleção
    	}else{
    		printf("\t.... Tela inicial ....\n\n"); //Inicio do menu
	        printf("Escolha a opção do menu:\n\n");
	        printf("\t 1) - Login \n");
	        printf("\t 2) - Cadastrar um usuário \n");
	        printf("\t 3) - Sair \n");
	        printf("Opção: "); //Fim do menu
	
	        scanf("%d", &option); //Armazenar escolha
	
	        system("cls");
	
	        switch (option) { //Inicio da seleção
		        case 1:
		            login();// funciona mas tem que melhorar
		        break;
		        case 2:
		            cadast();// funciona mas tem que melhorar
		        break; 
		        case 3:
		        	printf("Saindo...");
		        	return 0;
		        break;
		        default:
		            
		        break;
	        } //fim da seleção
    	}
	} 
    return 0;
}
//tela do chefe +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int boss(){
	setlocale(LC_ALL, "Portuguese"); //Definindo linguagem

    int option = 0; //Definindo a variavel
    int laco = 1;
    
	for (laco = 1; laco = 1;) {
        system("cls");
    
	    printf(".... Tela Boss ....\n\n"); //Inicio do menu
	    printf("Escolha a opção do menu:\n\n");
	    printf("\t 1) - Lista de usuários cadastrados\n");
	    printf("\t 2) - Consultar usuários\n");
	    printf("\t 3) - Apagar usuários\n");
		printf("\t 4) - Cadastrar produto\n");
	    printf("\t 5) - Lista de produtos cadastrados\n");
		printf("\t 6) - Consultar produto\n");
		printf("\t 7) - Emprestimo e devolução de produto\n");
		printf("\t 8) - Manutenção\n");
		printf("\t 9) - Apagar produto\n");
	    printf("\t 10) - Sair\n");
	    printf("Opção: "); //Fim do menu
	
	    scanf("%d", &option); //Armazenar escolha
	
	    system("cls");
	
	    switch (option) { //Inicio da seleção
		    case 1:
		    	show_user(users, nm_users);// funciona
		    break;
		    case 2:
		    	consult_user();// funciona
		    break;
		    case 3:
		    	del();// funciona
		    break;
		    case 4:
	        	cad_prod(prod_cad, &qntcad);// funciona
	        break;
	    	case 5:
	        	lista_prod(); // funciona
	        break;
	        case 6:
	        	consul_prod(prod_cad, qntcad); // funciona
	        break;
	        case 7:
	        	empr_prod(prod_cad, qntcad); // função não funcionando 
	        break;
	        case 8:
	        	manu_prod(prod_cad, qntcad);// funciona
	        break;
	    	case 9:
	        	apagar_prod(prod_cad, &qntcad);// funciona
	        break;
	    	case 10:
	        	printf("Saindo da conta.\n"); // Add a closing double quote
	        	system("pause");
	        	main();// volta pro menu
	    	break;
	    	default:
	        	
	    	break;
	    } //fim da seleção
	}
}

//tela funcionário ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int usua(){
	setlocale(LC_ALL, "Portuguese"); //Definindo linguagem

    int option = 0; //Definindo a variavel
    int laco = 1;
    
	do{//loop usando while ao invez de for
    	system("cls");
    
	    printf(".... Tela Produtos ....\n\n"); //Inicio do menu
	    printf("Escolha a opção do menu:\n\n");
	    printf("\t 1) - Cadastrar produto\n");
	    printf("\t 2) - Lista de produtos cadastrados\n");
		printf("\t 3) - Consultar produto\n");
		printf("\t 4) - Emprestimo e devolução de produto\n");
		printf("\t 5) - Manutenção\n");
		printf("\t 6) - Apagar produto\n");
	    printf("\t 7) - Sair\n");
	    printf("Opção: "); //Fim do menu
	
	    scanf("%d", &option); //Armazenar escolha
	
	    system("cls");
	
	    switch (option) {
	    	case 1:
	        	cad_prod(prod_cad, &qntcad);// funciona
	        break;
	    	case 2:
	        	lista_prod();// funciona
	        break;
	        case 3:
	        	consul_prod(prod_cad, qntcad);// funciona
	        break;
	        case 4:
	        	empr_prod(prod_cad, qntcad);// funciona
	        break;
	        case 5:
	        	manu_prod(prod_cad, qntcad);// funciona
	        break;
	    	case 6:
	        	apagar_prod(prod_cad, &qntcad);// funciona
	        break;
	    	case 7:
	        	printf("Saindo da conta.\n"); // Add a closing double quote
	        	system("pause");
	        	main();// volta pro menu
	    	break;
	    	default:
	        	
	    	break;
	    }
	} while (option != 7);
}