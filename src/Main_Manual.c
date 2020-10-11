


int main(){
        int choi;
        int lay;
	char color;
	char piece;
	char place;
        printf("**Welcome to Computer Chess**\n
                        Please choose from the following options:\n
                        1: Press 1 to play against another player\n
                        2: Press 2 to play against the computer\n
                        3: Press 3 to speculate comp. vs comp.\n
                        4: Press 4 to quit\n
                        Enter your selection: \n");
        scanf("%d",&choi);
        if(choi == 1){
        //PVP MODE
        }
	if(choi == 2){
	//PVC MODE
	}
	if(choi == 3){
	//CVC MODE
	}
	if(choi == 4){
	exit(0);

	}
	printf("Please select game board layout:\n
		1: Standard layout\n
		2: Choose layout manually\n\n
		Enter your selection: \n");
	scanf("%d",&lay);
	
	if(lay == 1){
	//Standard lay
	}
	if(lay == 2){
	//Manual lay
	}
	//Createboard
	//printboard
	printf("Please select the color that you would like to play(w for white, b for back):\n")
	scanf("%c",&color);
	while(/*not checkmate*/){
	printf("Select the piece that you would like to move:\n");
	scanf("%c",&piece);
	printf("Enter the game board coordinate for your move:\n")
	scanf("%c",&place);





	
}
}
