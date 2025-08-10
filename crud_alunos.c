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
void update_A(int n);
void delete_A(int n);

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
			listar_A();
			break;
		case 3:
			//editar alunos
			listar_A();
			int nid = 0;
			printf("qual id do aluno: ");
			scanf("%d", &nid);
			update_A(nid);
			break;
		case 4:
			//deletar alunos
			listar_A();
			int did = 0;
			printf("qual id do aluno: ");
			scanf("%d", &did);
			delete_A(did);
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
    fprintf(f, "%2d %39s %29s %5.1f %5.1f %5.1f\n", id, n.nome, n.curso, n.nota1, n.nota2, n.media);
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
    system("clear");
    FILE *f = fopen("alunos.txt", "r");
    char c;
    if (f == NULL){
        printf("erro");
    }
    else{
        while((c = fgetc(f)) != EOF){
            printf("%c", c);
        }
        printf("\n\n");
        pausa_seguir();
        fclose(f);
    }
}

void update_A(int n){
    FILE *t = fopen("temp.txt", "w");
    
    FILE *f = fopen("alunos.txt", "r");
    if (f == NULL){
        printf("arquivo nao encontrado");
        return;
    }
    
    ALUNO upd;
    int idn;
    
    while(fscanf(f, "%d %s %s %f %f %f", &idn, upd.nome, upd.curso, &upd.nota1, &upd.nota2, &upd.media) == 6){
        if(idn == n){
            ALUNO foda = adicionar_A();
            fprintf(t, "%2d %39s %29s %5.1f %5.1f %5.1f\n", idn, foda.nome, foda.curso, upd.nota1, foda.nota2, foda.media);
        }
        else{
            fprintf(t, "%2d %39s %29s %5.1f %5.1f %5.1f\n", idn, upd.nome, upd.curso, upd.nota1, upd.nota2, upd.media);
        }
    }
    fclose(f);
    fclose(t);
    remove("alunos.txt");
    rename("temp.txt", "alunos.txt");
    system("clear");
    printf("atualizado com exito");
}

void delete_A(int n){
    FILE *f = fopen("alunos.txt", "r");
    FILE *x = fopen("temp.txt", "w");
    
    ALUNO m;
    int upd = 1;
    
    while(fscanf(f, "%d %s %s %f %f %f", &upd, m.nome, m.curso, &m.nota1, &m.nota2, &m.media) == 6){
        if (upd == n){
            continue;
        }
        else{
            fprintf(x, "%2d %39s %29s %5.1f %5.1f %5.1f\n", upd, m.nome, m.curso, m.nota1, m.nota2, m.media);
        }
    }
    
    fclose(f);
    fclose(x);
    remove("alunos.txt");
    rename("temp.txt", "alunos.txt");
    system("clear");
    printf("deletado com exito\n\n");
    
    FILE *l = fopen("alunos.txt", "r");
    int linhas = 0;
    char linha[200];
    while(fgets(linha, sizeof(linha), l) != NULL){
        linhas++;
    }
    fclose(l);
    
    FILE *i = fopen("id.txt", "w");
    if (i == NULL){
        printf("erro ao abri o arquivo id.txt\n");
        return;
    }
    fprintf(i, "%d", linhas + 1);
    fclose(i);
}
