#include <stdio.h>
#include <stdlib.h>


typedef struct {
	int id;
	char nome[40];
	char curso[30];
	float nota1;
	float nota2;
	float media;
}ALUNO;

void salvar_A(int id, ALUNO n);
ALUNO adicionar_A();
int gerar_id();
void listar_A();

int main()
{
    int op = 0;
	do {
		printf("BEM VINDO\n");
		printf("MENU\n");
		printf("1- adicionar aluno\n2- listar alunos\n3- editar alunos\n4- deletar alunos\n99- sair\nopcao: ");
		scanf("%d", &op);

		switch(op) {
		case 1:
			//adicionar alunos
			int id = gerar_id();
			ALUNO novo = adicionar_A();
			salvar_A(id, novo);
			break;
		case 2:
			//listar alunos
			break;
		case 3:
			//editar alunos
			break;
		case 4:
			//deletar alunos
			break;
		case 99:
			//sair
			break;
		default:
			printf("opcao invalida");
			break;
		}
	}while(op != 99);

	return 0;
}

int gerar_id(){
    int id = 1;
    FILE *check = fopen("id.txt", "r");
    if(check == NULL){
        FILE *init = fopen("id.txt", "w");
        if(init != NULL){
            fprintf(init, "%d", id);
            fclose(init);
        }
        else{
            printf("erro na geracao de id");
            exit(0);
        }
    }
    else{
        fscanf(check, "%d", &id);
        fclose(check);
    }
    return id;
}

void Trans_Maius(char *str) {
	for(int i = 0; str[i] != '\0'; i++) {
		if(str[i] >= 'a' && str[i] <= 'z') {
			str[i] -= 32;
		}
	}
}


float calcular_media(float n, float m){
    float media = (n + m)/2;
    return media;
}

ALUNO adicionar_A(){
    int op = 0;
    ALUNO aln1;
    while(1){
        system("clear");
        printf("digite o nome: ");
        scanf("%39s", aln1.nome);
        printf("digite o curso: ");
        scanf("%29s", aln1.curso);
        printf("digite a primeira nota: ");
        scanf("%f", &aln1.nota1);
        printf("digite a segunda nota: ");
        scanf("%f", &aln1.nota2);
        aln1.media = calcular_media(aln1.nota1, aln1.nota2);
        
        printf("dados inseridos:\n");
        printf("NOME: %s\nCURSO: %s\nNOTA1: %.1f\nNOTA2: %.1f media: %.1f\n",
            aln1.nome, aln1.curso, aln1.nota1, aln1.nota2, aln1.media);
        printf("Deseja:\n1- salvar\n2- tentar novamente\n3- cancelar\nopcao: ");
        scanf("%d", &op);
        getchar();
        
        if(op == 1){
            //salvar ALUNO
            Trans_Maius(aln1.nome);
            Trans_Maius(aln1.curso);
            return aln1;
        }
        else if(op == 3){
            //sair
            break;
        }
    }
}


void salvar_A(int id, ALUNO n){

    FILE *f = fopen("alunos.txt", "a");
    if (f == NULL){
        printf("erro");
        system("clear");
    }
    fprintf(f, "%2d %39s %29s %.2f %.2f %.2f\n", id, n.nome, n.curso, n.nota1, n.nota2, n.media);
    fclose(f);
    
    FILE *i = fopen("id.txt", "w");
    if(i != NULL){
        fprintf(i, "%d", id + 1);
        fclose(i);
    }
    system("clear");
    printf("salvamento concluido");
}
void pausa_seguir(){
    printf("Aperte ENTER para continuar...");
	getchar();
	getchar();
	system("clear");
}

void listar_A(){
    FILE *f = fopen("alunos.txt", "r");
    char c;
    if (f == NULL){
        printf("erro");
        return EXIT_FAILURE;
    }
    else{
        while((c = fgetc(f)) != EOF){
            printf("%c", c);
        }
        pausa_seguir();
        fclose(f);
    }
}
