#include <iostream>

int main(){
    FILE * pFile;
  	pFile = fopen ( "example.txt" , "w" );
  	fputs ( "First line of output" , pFile );
  	fseek ( pFile , 11 , SEEK_SET );
  	fputs ( "Second line" , pFile );
  	fclose ( pFile );
}
