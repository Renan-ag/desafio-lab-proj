#include <stdio.h>
#include <math.h>
#include <locale.h>

typedef struct Character character;

struct Character{ // Estrutura personagem que vai ser o tipo de Heroi e Vilao
    char name[124]; // Nome com até 124 caracteres;
    int EP; // Energy points = pontos de energia;
    int PP; // Power points = pontos de poder;
};

//Variavel temporaria para scanf de strings com espaço 
char temp;

//Contante que define o limite maximo do valor de random
#define RANDOM_MAX_VALUE 100

// Metodo que exibe o menu e retorna o indice escolhido
int Menu(){
    system("cls");
	int selected_menu_index;

    printf("----	Simulador de combate Heroi VS Vilao	---- \n");
	printf("\n1 - Crie o Heroi \n");
	printf("\n2 - Crie o Vilao\n");
	printf("\n3 - Iniciar  luta\n");
	printf("\nEscolha uma das opcoes: ");
    scanf("%i", &selected_menu_index);

    return selected_menu_index;
}

// Metodo para passagem de valores para a variavel heroi
character* GetHero(character* Hero){
    system("cls");

    printf("Insira o nome do Heroi: ");
    scanf("%c",&temp);
	scanf("%[^\n]",Hero->name);
    
    printf("Quantos pontos de energia (numero inteiro) ele possui: ");
    scanf("%i", &Hero->EP);

    printf("Quantos pontos de poder (numero inteiro) ele possui: ");
    scanf("%i", &Hero->PP);
}

// Metodo para passagem de valores para a variavel vilão
character* GetVilain(character* Vilain){
    system("cls");

    printf("Insira o nome do Vilao: ");
    scanf("%c", &temp);
	scanf("%[^\n]",Vilain->name);
    
    printf("Quantos pontos de energia (numero inteiro) ele possui: ");
    scanf("%i", &Vilain->EP);

    printf("Quantos pontos de poder (numero inteiro) ele possui: ");
    scanf("%i", &Vilain->PP);

}

// Metodo que realiza o combate
void Battle(character* Hero, character* Vilain){
    // Variaveis de dano do heroi
    int hero_base_damage = round(Hero->PP/3);
    int hero_luck_damage = hero_base_damage + (hero_base_damage * 0.2);
    int hero_critical_damage = hero_base_damage * 2;

    // Variaveis de dano do vilao
    int vilain_base_damage = round(Hero->PP/3);
    int vilain_luck_damage = vilain_base_damage + (vilain_base_damage * 0.2);
    int vilain_critical_damage = vilain_base_damage * 2;

    // Variaveis de vida que serão atualizadas durante o combate
    int hero_life = Hero->EP;
    int vilain_life = Vilain->EP;
     
    // Variavel de que recebe valor randomico
    int random_number;

    //Geração da seed de randomização
    srand(time(NULL));
    
    system("cls");

    //Verificação para ver se algum dos lutadores tem vida inicial 0 ou não foi criado
    if(hero_life <= 0 || vilain_life <= 0){
        printf("Nao pode ocorrer a luta por conta de um WO...");
        getch();
        return;
    }

    printf("%s VS %s \n\n", Hero->name, Vilain->name);

    // Loop de combate
    while(hero_life != 0 && vilain_life != 0){ 

        // Logica do turno de ataque do Heroi
        random_number = rand()%RANDOM_MAX_VALUE;

        if(random_number >= 0 && random_number <= 15){
            printf("Turno do Heroi(HP: %i):\n", hero_life);
            printf("%s erra o ataque miseravelmente!\n\n", Hero->name);
        }
    
        else if(random_number >= 16 && random_number <= 70){
            vilain_life -= hero_base_damage;
            printf("Turno do Heroi(HP: %i):\n", hero_life);
            printf("%s ataca e causa %i de dano!\n\n", Hero->name, hero_base_damage);
        }
        
        else if (random_number >= 71 && random_number <= 96){
            vilain_life -= hero_luck_damage;
            printf("Turno do Heroi(HP: %i):\n", hero_life);
            printf("%s ataca ferozmente causando %i de dano!\n\n", Hero->name, hero_luck_damage);
        }
        
        else {
            vilain_life -= hero_critical_damage;
            printf("Turno do Heroi(HP: %i):\n", hero_life);
            printf("%s ataca um ponto vital do oponente causando %i de dano!\n\n", Hero->name, hero_critical_damage);
        }

        if(vilain_life <= 0){
            printf("\n%s derrotou o %s...", Hero->name, Vilain->name);
            break;
        }

        // Logica do turno de ataque do vilao 
        random_number = rand()%RANDOM_MAX_VALUE;

        if(random_number >= 0 && random_number <= 15){
            printf("Turno do Vilao (HP: %i):\n", vilain_life);
            printf("%s erra o ataque miseravelmente!\n\n", Vilain->name);
        }
    
        else if(random_number >= 16 && random_number <= 70){
            hero_life -= vilain_base_damage;
            printf("Turno do Vilao (HP: %i):\n", vilain_life);
            printf("%s ataca e causa %i de dano!\n\n", Vilain->name, vilain_base_damage);
        }
        
        else if (random_number >= 71 && random_number <= 96){
            hero_life -= vilain_luck_damage;
            printf("Turno do Vilao (HP: %i):\n", vilain_life);
            printf("%s ataca ferozmente causando %i de dano!\n\n", Vilain->name, vilain_luck_damage);
        }
        
        else {
            hero_life -= vilain_critical_damage;
            printf("Turno do Vilao (HP: %i):\n", vilain_life);
            printf("%s ataca um ponto vital do oponente causando %i de dano!\n\n", Vilain->name, vilain_critical_damage);
        }

        if(hero_life <= 0){
            printf("\n%s derrotou o %s...", Vilain->name, Hero->name);
            break;
        }
    }

    getch();
}

void main(){
    // Criando variaveis e alocando memorias para elas  
    character* hero = (character*)malloc(sizeof(character));
    character* vilain = (character*)malloc(sizeof(character));

    // GameLoop
    while(1){
        switch(Menu()){
            case 1:
                GetHero(hero);
            break;
            case 2:
                GetVilain(vilain);
            break;
            case 3:
                Battle(hero, vilain);
            break;
            default:
                printf("Opcao inexistente...");
                getch();
            break;
        }
    }   
}