#include <string.h>
#include <stdio.h>
#define MAX_BOOKS 100

struct Book{
    int id;
    char title[50];
    char author[50];
    int is_borrowed;
    int student_id;
    
};



struct Library{
    struct Book books[MAX_BOOKS]; // Kütüphanenin kitap kapasitesini gösterir
    int book_count;  // Kütüphanenin içinde güncel olarak kaç tane kitap oldugunu gösterir
};


 void addBook(struct Library*library,int id,const char *title,const char *author){
    if(library->book_count<MAX_BOOKS){
        if(strlen(title)==0 || strlen(author)==0){
            printf("Gecersiz giris. Lutfen kitap ismi ve yazarini girin...\n");
            return;
        }
        
        
        struct Book newBook;
        newBook.id=id;
        strcpy (newBook.title,title);
        strcpy(newBook.author,author);
        newBook.is_borrowed=0;
        newBook.student_id=-1;// Kimse kitabi odunc almadıgi icin -1 kullandik.
        
        
        library->books[library->book_count++] =newBook; // Eklenen kitaplari newBook
                                                       // değiskenine yerlestirmemizi sagliyor 
        printf("*Kitap eklendi*\n");                   
        
    }
    else{
        printf("Kutuphanede bos yer yok,kitap ekleme islemi yapilamiyor!!!");
    }
}
 void listAllBooks(struct Library *library){
     if(library->book_count==0){
         printf("Kutuphane bos!!!\n");
         return;
     }
    
    printf("All Books: \n");
    printf("%-5d %-20s %-20s %-10s\n","ID","Title","Author","Status");
    printf("---------------------------------------------------------------\n");
    
    int i;
    for(i=0;i<library->book_count;i++){
        printf("%-5d %-20s %-20s %-10s\n",library->books[i].id,library->books[i].title,library->books[i].author,library->books[i].is_borrowed ?
            "Borrowed" :"Avaliable");
        
    }
 }
 
 void search(struct Library *library,int id){
     for(int i=0;i<library->book_count;i++){
         if(library->books[i].id==id){
             printf("Kitap bulundu!!!");
             printf("ID: %d\n",library->books[i].id);
             printf("TITLE: %s\n",library->books[i].title);
             printf("AUTHOR: %s\n",library->books[i].author);
             printf("STATUS: %s\n",library->books[i].is_borrowed ? "Borrowed" : "Avaliable");
             printf("Student ID: %d\n",library->books[i].student_id);
             return;
         }
     }
     
    printf("Aradiginiz kitap bulunamadi!!!\n");
 }
 
 
 void borrowBook(struct Library *library,int id,int student_id){
    int i;
    for(i=0;i<library->book_count;i++){
        if(library->books[i].id==id){
            if(library->books[i].is_borrowed); // Kitap eger odunc alindi ise ekrana uyari mesaji cikacak
               printf("Bu kitap zaten  kiralanmis!!!\n");
               
            } else{
                library->books[i].is_borrowed=1;
                library->books[i].student_id=student_id;
                printf("Kitap kiralandi...n");
        }
        return;
    }
       printf(" Girdiginiz ID numarasina sahip bir kitap bulunamadi!!!\n");
  
} 
  
 void returnBook(struct Library *library,int id){
      for(int i=0;i<library->book_count;i++){
          
            if(library->books[i].id==id){
                
                if(library->books[i].is_borrowed){
                    library->books[i].is_borrowed=0;
                    library->books[i].student_id=-1;
                    printf("Kitap kütüphaneye iade edildi...\n");
                    
                  
                    
                } else {
                    printf("Bu kitap zaten kütüphanede...\n");
                   
                }
                return;
                
            }
          
      }
     printf(" Girdiginiz ID numarasina sahip bir kitap bulunamadi!!!\n");
     
     
 }

int main()
{
    struct Library library;
    library.book_count=0;
    int student_id,id;
    int choice;
    char title[50],author[50];
    
   
	do {
		printf("\nKutuphane Yonetim Sistemi\n");
        
		printf("1.Add Book\n");
		printf("2.List All Books\n");
		printf("3.Search Book By ID\n");
		printf("4.Rent Book\n");
		printf("5.Return Book\n");
		printf("0.Exit Book\n");
		
		
		printf("Enter your choice:");
		scanf("%d",&choice);
		switch(choice){
		    case 1:
		        printf("ID: ");
		        scanf("%d",&id);
		        printf("Title: ");
		        getchar();// int den sonra string tipinde bir veri aldığımız için bir önceki 
		             // scanf'teki new line'ı temizledik. Yoksa yanlış çalışır.
                gets(title);
                printf("Author: ");
                gets(author);
                addBook(&library,id,title,author);
                break;
            case 2:
                 listAllBooks(&library); 
                 break;
            case 3:
                 printf("Lutfen kitap ID girin: ");
                 scanf("%d",&id);
                 search(&library,id);
                 break;
            case 4:
                 printf("Lutfen kitap ID girin: ");
                 scanf("%d\n",&id);
                 printf("Lutfen ogrenci ID girin: ");
                 scanf("%d\n",&student_id);
                 borrowBook(&library,id,student_id);
                 break;
            case 5:
                 printf("İade edilecek kitabin ID'sini girin: ");
                 scanf("%d\n",&id);
                 returnBook(&library,id);
                 break;
            case 0:
                 printf("CİKİS YAPİLDİ!\n");
                 break; 
            default:
                 printf("Gecersiz secim girdiniz.Tekrar deneyin!!!!");
		}


	}   while(choice!=0);
	 
	 return 0;
	
}

