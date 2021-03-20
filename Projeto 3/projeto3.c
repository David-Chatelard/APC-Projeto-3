/**
 *	      @file: trabalho03.c
 *	    @author: David Fanchic Chatelard 180138863
 *	@disciplina: Algoritmos e Programacao de Computadores
 *	O progarama consiste em receber um arquivo binário e gerar
 *	um arquivo de texto com essas informações e cifrar ou decifar
 *	as informações(usando a cifra de vigenère) e as armazenar em um arquivo binário.
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define TAM_ALFABETO 26

typedef struct{
	char nome[20], dieta[15], nome_cod[20], dieta_cod[15];
	int tempo_vida, qi;
	float estatura, peso;
} __attribute__ ((packed)) alien_t;

char cifra_letra(char letra_normal, char letra_chave){
	if (letra_normal == ' '){
		return letra_normal;
	}
	if ((letra_normal >= 'a') && (letra_normal <= 'z')){
		if ((letra_normal + letra_chave) > 'z'){
			return ((letra_normal + letra_chave) - TAM_ALFABETO);
		}
		else{
			return (letra_normal + letra_chave);
		}
	}
	else if ((letra_normal >= 'A') && (letra_normal <= 'Z')){
		if ((letra_normal + letra_chave) > 'Z'){
			return ((letra_normal + letra_chave) - TAM_ALFABETO);
		}
		else{
			return (letra_normal + letra_chave);
		}
	}
	/*A linha abaixo é para evitar um aviso na hora de compilar.*/
	return '0';
}

void cifra_vigenere(alien_t *alien, char chave[9]){
	int tam, i, j;
	char chave_aux1[20+15+1], chave_aux2[20+15+1];

	/*As 7 linhas abaixo são para formar o tamanho certo da chave para cifrar o nome e a dieta do alien.*/
	tam = (strlen((*alien).nome) + (strlen((*alien).dieta)));
	strcpy(chave_aux1, chave);
	while(strlen(chave_aux1) < tam){
		strcat(chave_aux1, chave);
	}
	strncpy(chave_aux2, chave_aux1, tam);
	chave_aux2[tam] = '\0';
	/*O laço de repetição é para cifrar as letras do nome e da dieta.*/
	for (i = 0, j = 0; i < tam; i++, j++){
		if (i < strlen((*alien).nome)){
			(*alien).nome_cod[i] = cifra_letra((*alien).nome[i], (chave_aux2[j] - 'a'));
			if ((*alien).nome[i] == ' '){
				j--;
			}
		}
		else{
			(*alien).dieta_cod[i - strlen((*alien).nome)] = cifra_letra((*alien).dieta[i - strlen((*alien).nome)], (chave_aux2[j] - 'a'));
			if ((*alien).dieta[i - strlen((*alien).nome)] == ' '){
				j--;
			}
		}
	}
	(*alien).nome_cod[strlen((*alien).nome)] = '\0';
	(*alien).dieta_cod[strlen((*alien).dieta)] = '\0';
}

void decifra_vigenere(alien_t *alien, char chave[9]){
	int tam, i, j;
	char chave_aux1[20+15+1], chave_aux2[20+15+1];

	/*As 7 linhas abaixo são para formar o tamanho certo da chave para decifrar o nome e a dieta do alien.*/
	tam = (strlen((*alien).nome) + (strlen((*alien).dieta)));
	strcpy(chave_aux1, chave);
	while(strlen(chave_aux1) < tam){
		strcat(chave_aux1, chave);
	}
	strncpy(chave_aux2, chave_aux1, tam);
	chave_aux2[tam] = '\0';
	/*O laço de repetição é para decifrar as letras do nome e da dieta.*/
	for (i = 0, j = 0; i < tam; i++, j++){
		if (i < strlen((*alien).nome)){
			(*alien).nome_cod[i] = cifra_letra((*alien).nome[i], (TAM_ALFABETO - (chave_aux2[j] - 'a')));
			if ((*alien).nome[i] == ' '){
				j--;
			}
		}
		else{
			(*alien).dieta_cod[i - strlen((*alien).nome)] = cifra_letra((*alien).dieta[i - strlen((*alien).nome)], (TAM_ALFABETO - (chave_aux2[j] - 'a')));
			if ((*alien).dieta[i - strlen((*alien).nome)] == ' '){
				j--;
			}
		}
	}
	(*alien).nome_cod[strlen((*alien).nome)] = '\0';
	(*alien).dieta_cod[strlen((*alien).dieta)] = '\0';
}

int main(){
	alien_t alien[10];
	FILE *fmensagem = fopen("mensagem.bin", "rb");
	FILE *fespecies = fopen("especies.txt", "w");
	FILE *fcodificado = fopen("codificado.bin", "wb");
	char chave[9] = "ehotruvs", opcao_cifrar;
	int n, i, teste;

	if (fmensagem == NULL){
		printf("Não foi possível abrir o arquivo.\n");
		return EXIT_FAILURE;
	}
	if (fespecies == NULL){
		printf("Não foi possível criar o arquivo de texto.\n");
		return EXIT_FAILURE;
	}
	if (fcodificado == NULL){
		printf("Não foi possível criar o arquivo binário.\n");
		return EXIT_FAILURE;
	}
	/*As linhas até o final do laço de repetição, são para ler as informações do arquivo binário e escrever no arquivo de texto.*/
	fread(&n, sizeof(n), 1, fmensagem);
	fprintf(fespecies, "%d\n", n);
	for (i = 0; i < n; i++){
		fread(alien[i].nome, sizeof(alien[i].nome), 1, fmensagem);
		fread(alien[i].dieta, sizeof(alien[i].dieta), 1, fmensagem);
		fread(&alien[i].tempo_vida, sizeof(alien[i].tempo_vida), 1, fmensagem);
		fread(&alien[i].qi, sizeof(alien[i].qi), 1, fmensagem);
		fread(&alien[i].estatura, sizeof(alien[i].estatura), 1, fmensagem);
		fread(&alien[i].peso, sizeof(alien[i].peso), 1, fmensagem);
		fprintf(fespecies, "%s\n", alien[i].nome);
		fprintf(fespecies, "%s\n", alien[i].dieta);
		fprintf(fespecies, "%d\n", alien[i].tempo_vida);
		fprintf(fespecies, "%d\n", alien[i].qi);
		fprintf(fespecies, "%f\n", alien[i].estatura);
		fprintf(fespecies, "%f\n", alien[i].peso);
		fprintf(fespecies, "\n\n");
	}
	system("clear");
	printf("                    ******************************\n");
	printf("                                 MENU\n");
	printf("                    ******************************\n\n");
	do{
		teste = 0;
		printf("Digite 'c' para cifrar as informações recebidas e criar o arquivo binário.\n");
		printf("Digite 'd' para decifrar as informações recebidas e criar o arquivo binário.\n");
		printf("Digite 'x' para sair do programa.\n");
		scanf("%c", &opcao_cifrar);
		while(getchar() != '\n'){
			teste++;
		}
		opcao_cifrar = tolower(opcao_cifrar);
		if ((teste != 0) || ((opcao_cifrar != 'c') && (opcao_cifrar != 'd') && (opcao_cifrar != 'x'))){
			printf("Digite somente uma letra válida!!('c', 'd' ou 'x')\n");
		}
		else{
			if (opcao_cifrar == 'x'){
				return EXIT_SUCCESS;
			}
			else if ((opcao_cifrar == 'd')){
				/*O laço de repetição abaixo decifra um registro por vez.*/
				for (i = 0; i < n; i++){
					decifra_vigenere(&alien[i], chave);
				}
				system("clear");
				break;
			}
			else if (opcao_cifrar == 'c'){
				/*O laço de repetição abaixo cifra um registro por vez.*/
				for (i = 0; i < n; i++){
					cifra_vigenere(&alien[i], chave);
				}
				system("clear");
				break;
			}
		}
	} while(1);
	/*As linhas até o final do laço de repetição, são para escrever no arquivo codificado.*/
	fwrite(&n, sizeof(n), 1, fcodificado);
	for (i = 0; i < n; i++){
		fwrite(alien[i].nome_cod, sizeof(alien[i].nome_cod), 1, fcodificado);
		fwrite(alien[i].dieta_cod, sizeof(alien[i].dieta_cod), 1, fcodificado);
		fwrite(&alien[i].tempo_vida, sizeof(alien[i].tempo_vida), 1, fcodificado);
		fwrite(&alien[i].qi, sizeof(alien[i].qi), 1, fcodificado);
		fwrite(&alien[i].estatura, sizeof(alien[i].tempo_vida), 1, fcodificado);
		fwrite(&alien[i].peso, sizeof(alien[i].peso), 1, fcodificado);
	}
	fclose(fmensagem);
	fclose(fespecies);
	fclose(fcodificado);

	return EXIT_SUCCESS;
}
