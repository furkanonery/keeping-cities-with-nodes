#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void SonaEkle2(int,char[],char[],int);
void menu();
void SonaEkle1(int,char[],char[],int);
int komsuPlakaBul(char[]);
void komsuPlakaEkle(int*,int,char[]);
void yazdir();
int sehirVarMi(char[]);
int plakaVarMi(int);
void komsulukEkle(char[],char[]);
void komsuSayisiAzalt(char[]);
struct sehir *araPlaka(int);
struct sehir *araSehir(char[]);
void komsuBilgileriGosterPlaka(int,int);
void komsuBilgileriGosterSehir(char[],int );
void plakadanBilgiGoster(int);
void sehirSil(int);
void silinenSehrinKomsuluklariniSil(int);
void komsulukSil(char[],char[]);
void bolgeListele(char[]);
void degerListele(int);
void Sirala();
int komsuMu(char[],char[]);

struct komsu
{
    int komsuPlaka;
    struct komsu *front;
};
struct sehir
{
    char cografiBolge[3];
    int komsuSayisi;
    char sehirAdi[20];
    int plakaKodu;
    int *komsuPlakalar;

    struct komsu *komsuPlaka;

    struct sehir *front;
    struct sehir *back;
};
struct sehir *cityBAS=NULL,*citySON=NULL;
int main()
{
    char satir[256];
    FILE *ptr;
    ptr=fopen("sehirler2.txt","r+");
    FILE *yaz;
    yaz=fopen("cikti.txt","a");
    if(ptr==NULL)
    {
        printf("Dosya Bulunamadi...");
        return;
    }
    while(!feof(ptr))
    {
        int komsuSayisi=-2;
        fgets(satir,256,ptr);
        for(int i=0; i<strlen(satir); i++)
        {
            if(satir[i]==',')
            {
                satir[i]=' ';
                komsuSayisi++;
            }
        }
        char cografiBolge[2];
        char sehir[20];
        int plakaKodu;
        sscanf(satir,"%d %s %s",&plakaKodu,sehir,cografiBolge);
        //SonaEkle1(plakaKodu,sehir,cografiBolge,komsuSayisi);
        SonaEkle2(plakaKodu,sehir,cografiBolge,komsuSayisi);
    }
    //yazdir();
    rewind(ptr);
    while(!feof(ptr))
    {
        int kelime=1;
        fgets(satir,256,ptr);
        int uzunluk=strlen(satir);

        char cumleayir[20][20];
        for(int i=0; i<uzunluk; i++)
        {
            if(satir[i]==',')
            {
                kelime++;
                satir[i]='\0';
            }
        }
        satir[uzunluk-1]='\0';
        int j=0;
        int k=0;
        for(int i=0; i<kelime; i++)
        {
            strcpy(cumleayir[i],satir+1+i+k);
            while(j<=i)
            {
                k += strlen(cumleayir[j]);
                j++;
            }
        }
        strcpy(cumleayir[0],satir);

        int *dizi=(int*)malloc((kelime)*sizeof(int));
        //printf("%d:",atoi(cumleayir[0]));
        for(int i=3; i<kelime; i++)
        {
            dizi[i-3]=komsuPlakaBul(cumleayir[i]);
            //printf(" %s ",cumleayir[i]);

        }
        /*printf("\n");
        for(int i=0;i<kelime-3;i++)
        {
            printf("%d ",dizi[i]);
        }
        printf("\n");*/
        //dizi[kelime-4]=komsuPlakaBul(cumleayir[kelime-1]);
        komsuPlakaEkle(dizi,kelime-3,cumleayir[1]);
        //printf("\n");
        free(dizi);
    }
    Sirala();
    //yazdir();
    while(1)
    {
        menu();
        int secim;
        printf("SECIM:");
        scanf("%d",&secim);
scm:
        if(secim==1)
        {
            int plaka;
            char sehir[20];
            char cografiBolge[3];
            int komsuSayisi=0;
yeni1:
            printf("Sehir ismi:");
            scanf("%s",sehir);
            sehir[0]=toupper(sehir[0]);
            if(sehirVarMi(sehir)==1)
            {
                printf("Zaten bu sehir isminden bir tane var yenisini girin.....\n");
                goto yeni1;
            }
yeni2:
            printf("Plaka:");
            scanf("%d",&plaka);
            if(plakaVarMi(plaka)==1)
            {
                printf("Zaten bu plakaya sahip bir sehir var yenisini girin.....\n");
                goto yeni2;
            }
            printf("Cografi bolge:");
            scanf("%s",cografiBolge);
            cografiBolge[0]=toupper(cografiBolge[0]);
            cografiBolge[1]=toupper(cografiBolge[1]);
            SonaEkle2(plaka,sehir,cografiBolge,0);

            Sirala();
            printf("\n%s sehir listesine eklendi.\n\n",sehir);
            fprintf(yaz,"\n%s sehir listesine eklendi.\n\n",sehir);
        }
        else if(secim==2)
        {
            FILE *ptr2;
            ptr2=fopen("cikti.txt","a");
            char sehir1[20];
            char sehir2[20];
            printf("Komsu olarak eklemek istediginiz iki sehri girin....\n");
            printf("Sehir1:");
            scanf("%s",&sehir1);
            printf("Sehir2:");
            scanf("%s",&sehir2);
            sehir1[0]=toupper(sehir1[0]);
            sehir2[0]=toupper(sehir2[0]);
            if(komsuMu(sehir1,sehir2)==0)
            {
                printf("%s ve %s sehirleri zaten birbirlerinin komsusu...\n\n",sehir1,sehir2);
                fprintf(ptr2,"%s ve %s sehirleri zaten birbirlerinin komsusu...\n\n",sehir1,sehir2);
            }
            else
            {
                printf("%s ve %s sehirlerinin komsuluklari olustu...\n\n",sehir1,sehir2);
                fprintf(ptr2,"%s ve %s sehirlerinin komsuluklari olustu...\n\n",sehir1,sehir2);
            }
            komsulukEkle(sehir1,sehir2);
            Sirala();
        }
        else if(secim==3)
        {
            FILE *ptr2;
            ptr2=fopen("cikti.txt","a");
            int code;
            char name[20];
            char CB[3];
            int neighValue;
            printf("Aramak istediginiz sehrin ismini veya plakasini girin:");
            scanf("%s",name);
            name[0]=toupper(name[0]);
            code=atoi(name);
            if(code<200 && code>0)
            {

                struct sehir *ara=araPlaka(code);
                if(ara==NULL)
                {
                    printf("Sehir veya Plaka listede yok eklemek icin 1'i tuslayin:");
                    scanf("%d",&secim);
                    if(secim==1)
                    {
                        goto scm;
                    }
                    continue;
                }
                printf("Girdiginiz plakaya gore bulunan sehir:\n");
                printf("Plaka kodu:%d \nSehir adi:%s \n Cografi bolge:%s \n Komsu Sayisi:%d\n",ara->plakaKodu,ara->sehirAdi,ara->cografiBolge,ara->komsuSayisi);
                fprintf(ptr2,"\nGirdiginiz plakaya gore bulunan sehir:\n");
                fprintf(ptr2,"Plaka kodu:%d \nSehir adi:%s \n Cografi bolge:%s \n Komsu Sayisi:%d\n",ara->plakaKodu,ara->sehirAdi,ara->cografiBolge,ara->komsuSayisi);
                fprintf(ptr2,"Komsu bilgileri:\n");
                komsuBilgileriGosterPlaka(code,ara->komsuSayisi);

            }
            else
            {
                struct sehir *ara=araSehir(name);
                if(ara==NULL)
                {
                    printf("Sehir veya Plaka listede yok eklemek icin 1'i tuslayin:");
                    scanf("%d",&secim);
                    if(secim==1)
                    {
                        goto scm;
                    }
                    continue;
                }
                printf("Girdiginiz isme gore bulunan sehir:\n");
                fprintf(ptr2,"\nGirdiginiz isme gore bulunan sehir:\n");
                printf("Plaka kodu:%d \nSehir adi:%s \n Cografi bolge:%s \n Komsu Sayisi:%d\n",ara->plakaKodu,ara->sehirAdi,ara->cografiBolge,ara->komsuSayisi);
                fprintf(ptr2,"Plaka kodu:%d \nSehir adi:%s \n Cografi bolge:%s \n Komsu Sayisi:%d\n",ara->plakaKodu,ara->sehirAdi,ara->cografiBolge,ara->komsuSayisi);
                printf("Komsu bilgileri:\n");
                fprintf(ptr2,"Komsu bilgileri:\n");
                komsuBilgileriGosterSehir(name,ara->komsuSayisi);
            }
        }
        else if(secim==4)
        {
            FILE *ptr2;
            ptr2=fopen("cikti.txt","a");
            printf("Sehir silmek icin:1\nKomsuluk silmek icin:2\n");
            printf("Secim:");
            scanf("%d",&secim);
            if(secim==1)
            {
                printf("Silmek istediginiz sehrin ismini veya plakasini girin:");
                int code;
                char name[20];
                scanf("%s",name);
                name[0]=toupper(name[0]);
                code=atoi(name);
                if(code<200 && code>0)
                {
                    //printf("plaka");
                    if(plakaVarMi(code)==0)
                    {
                        printf("Girdiginiz plakaya sahip bir sehir bulunamadi..\n");
                        fprintf(ptr2,"Girdiginiz plakaya sahip bir sehir bulunamadi..\n");
                        continue;
                    }
                    else if(plakaVarMi(code)==1)
                    {
                        printf("%s sehirler listesinden silindi..\n",araPlaka(code)->sehirAdi);
                        fprintf(ptr2,"%s sehirler listesinden silindi..\n",araPlaka(code)->sehirAdi);
                        sehirSil(code);
                    }
                }
                else
                {
                    code=komsuPlakaBul(name);
                    if(plakaVarMi(code)==0)
                    {
                        printf("Girdiginiz sehir ismine sahip bir sehir bulunamadi..\n");
                        fprintf(ptr2,"Girdiginiz sehir ismine sahip bir sehir bulunamadi..\n");
                        continue;
                    }
                    else if(plakaVarMi(code)==1)
                    {
                        printf("%s sehirler listesinden silindi..\n",araPlaka(code)->sehirAdi);
                        fprintf(ptr2,"%s sehirler listesinden silindi..\n",araPlaka(code)->sehirAdi);
                    }
                    sehirSil(code);
                }
            }
            else if(secim==2)
            {
                char sehir1[20];
                char sehir2[20];
                printf("Komsuluklarini silmek istediginiz iki sehri girin....\n");
                printf("Sehir1:");
                scanf("%s",&sehir1);
                printf("Sehir2:");
                scanf("%s",&sehir2);
                sehir1[0]=toupper(sehir1[0]);
                sehir2[0]=toupper(sehir2[0]);
                if(komsuMu(sehir1,sehir2)==0)
                {
                    printf("%s ve %s sehirlerinin komsuluklari silindi..\n",sehir1,sehir2);
                    fprintf(ptr2,"%s ve %s sehirlerinin komsuluklari silindi..\n",sehir1,sehir2);
                    komsulukSil(sehir1,sehir2);
                }
                else if(komsuMu(sehir1,sehir2)==1)
                {
                    printf("%s ve %s sehirleri zaten birbirine komsu degil..\n",sehir1,sehir2);
                    fprintf(ptr2,"%s ve %s sehirleri zaten birbirine komsu degil..\n",sehir1,sehir2);
                }
            }
            Sirala();
        }
        else if(secim==5)
        {
            char bolge[2];
            printf("Bolge ismini girin(GA,DA,AK,MA,KA,IA,EG):");
            scanf("%s",bolge);
            bolge[0]=toupper(bolge[0]);
            bolge[1]=toupper(bolge[1]);
            bolgeListele(bolge);
        }
        else if(secim==6)
        {
            int deger;
            printf("Deger girin:");
            scanf("%d",&deger);
            degerListele(deger);
        }
        else if(secim==7)
        {
            yazdir();
        }
        else
        {
            return 0;
        }
    }

    return 0;
}
void menu()
{
    printf("SEHIR EKLE(1)\n\n");//tamamlandi
    printf("KOMSULUK EKLE(2)\n\n");//tamalandi
    printf("SEHIR ISMI VEYA PLAKA KODUYLA ARAMA YAP(3)\n\n");//tamamlandi
    printf("BIR SEHRI VEYA KOMSULUK KAYDINI SILIN(4)\n\n");
    printf("BIR BOLGEDEKI SEHIRLERI LISTELEYIN(5)\n\n");//tamamlandi
    printf("BIR DEGER GIRIN VE KOMSU SAYISI BU DEGERDEN FAZLA OLAN SEHIRLERI GORUN(6)\n\n");//tamamlandi
    printf("TUM SEHIRLERI LISTELE(7)\n\n");//tamamlandi
    // printf("BELLI BIR SAYI ARALIGINDA KOMSU SAYISINA SAHIP SEHIRLERDEN\nBELIRLI ORTAK KOMSULARA SAHIP SEHIRLER(8)\n\n ");
    printf("-----------------------------------------------------------------------------\n");
    printf("                  HOSGELDINIZ\n           CIKMAK ICIN BASKA TUSA BASIN\n");//tamamlandi
}
//************************************************************************
//************************************************************************
/*void SonaEkle1(int plaka,char sehir[],char bolge[],int komsuSayisi)
{
    struct sehir *yeni = (struct sehir*) malloc(sizeof(struct sehir));
    yeni->komsuPlakalar=(int*)malloc(sizeof(int)*(komsuSayisi+1));

    strcpy(yeni->cografiBolge,bolge);
    yeni->komsuSayisi=komsuSayisi;
    strcpy(yeni->sehirAdi,sehir);
    yeni->plakaKodu=plaka;
    if(cityBAS==NULL)
    {
        cityBAS=yeni;
        citySON=yeni;
        citySON->front=NULL;
    }
    else
    {
        citySON->front=yeni;
        citySON=yeni;
        citySON->front=NULL;
    }
}*/
//****************************************************************************
void SonaEkle2(int plaka,char sehir[],char bolge[],int komsuSayisi)
{
    struct sehir *yeni = (struct sehir*) malloc(sizeof(struct sehir));
    yeni->komsuPlakalar=(int*)malloc(sizeof(int)*(komsuSayisi));
    strcpy(yeni->cografiBolge,bolge);
    yeni->komsuSayisi=komsuSayisi;
    strcpy(yeni->sehirAdi,sehir);
    yeni->plakaKodu=plaka;

    if(cityBAS==NULL)
    {
        cityBAS=yeni;
        citySON=yeni;
        citySON->front=citySON;
        citySON->back=cityBAS;
    }
    else
    {
        citySON->front=yeni;
        yeni->back=citySON;
        yeni->front=cityBAS;
        cityBAS->back=yeni;
        citySON=yeni;

    }
}
//****************************************************************************
int komsuPlakaBul(char sehir[])
{
    struct sehir *ara=cityBAS;
    while(ara->front!=cityBAS)
    {
        if(strncmp(ara->sehirAdi,sehir,strlen(ara->sehirAdi)-1)==0)
        {
            return ara->plakaKodu;
        }
        ara=ara->front;
    }
    if(strncmp(ara->sehirAdi,sehir,strlen(ara->sehirAdi)-1)==0)
    {
        return ara->plakaKodu;
    }
    return NULL;
}
void komsuPlakaEkle(int *dizi,int KS,char sehir[])
{
    for(int i=0; i<KS; i++)
    {
        for(int j=i+1; j<KS; j++)
        {
            if(dizi[i]>dizi[j])
            {
                int temp=dizi[i];
                dizi[i]=dizi[j];
                dizi[j]=temp;
            }
        }
    }
    struct sehir *ara=cityBAS;
    while(ara->front!=cityBAS)
    {
        if(strcmp(ara->sehirAdi,sehir)==0)
        {

            //ara->komsuPlakalar=(int*)malloc(sizeof(int)*KS);
            for(int i=0; i<KS; i++)
            {
                *(ara->komsuPlakalar+i)=*(dizi+i);
            }
        }
        //free(ara->komsuPlakalar);
        ara=ara->front;
    }
    if(strcmp(ara->sehirAdi,sehir)==0)
    {

        //ara->komsuPlakalar=(int*)malloc(sizeof(int)*KS);
        for(int i=0; i<KS; i++)
        {
            *(ara->komsuPlakalar+i)=*(dizi+i);
        }
    }
}
//****************************************************************************
void yazdir()
{
    struct sehir *liste=cityBAS;
    FILE *yaz;
    yaz=fopen("cikti.txt","a");


    fprintf(yaz,"\nTum sehirlerin listesi:\n");
    while(liste->front!=cityBAS)
    {
        if(liste->plakaKodu != 0)
        {
            printf("%d %s Bolge:%s Komsu Sayisi:%d ",liste->plakaKodu,liste->sehirAdi,liste->cografiBolge,liste->komsuSayisi);
            printf("Komsu plakalar:");
            fprintf(yaz,"%d %s Bolge:%s Komsu Sayisi:%d ",liste->plakaKodu,liste->sehirAdi,liste->cografiBolge,liste->komsuSayisi);
            fprintf(yaz,"Komsu plakalar:");
            for(int i=0; i<liste->komsuSayisi; i++)
            {
                printf("->%d",liste->komsuPlakalar[i]);
                fprintf(yaz,"->%d",liste->komsuPlakalar[i]);
            }
            printf("\n");
            fprintf(yaz,"\n");
        }
        liste=liste->front;
    }
    printf("%d %s Bolge:%s Komsu Sayisi:%d ",liste->plakaKodu,liste->sehirAdi,liste->cografiBolge,liste->komsuSayisi);
    printf("Komsu plakalar:");
    fprintf(yaz,"%d %s Bolge:%s Komsu Sayisi:%d ",liste->plakaKodu,liste->sehirAdi,liste->cografiBolge,liste->komsuSayisi);
    fprintf(yaz,"Komsu plakalar:");
    for(int i=0; i<liste->komsuSayisi; i++)
    {
        printf("->%d",liste->komsuPlakalar[i]);
        fprintf(yaz,"->%d",liste->komsuPlakalar[i]);
    }
    printf("\n");
    fprintf(yaz,"\n");
}
//***************************************************************************
int sehirVarMi(char sehir[])
{
    struct sehir *liste=cityBAS;
    while(liste->front!=cityBAS)
    {
        if(strcmp(sehir,liste->sehirAdi)==0)
        {
            return 1;
        }
        liste=liste->front;
    }
    if(strcmp(sehir,liste->sehirAdi)==0)
    {
        return 1;
    }

    return 0;
}
int plakaVarMi(int plaka)
{
    struct sehir *liste=cityBAS;
    while(liste->front!=cityBAS)
    {
        if(plaka==liste->plakaKodu)
        {
            return 1;
        }
        liste=liste->front;
    }
    if(plaka==liste->plakaKodu)
    {
        return 1;
    }

    return 0;
}
//***************************************************************************
int komsuMu(char sehir1[],char sehir2[])
{
    struct sehir *ara=cityBAS;
    while(ara->front!=cityBAS)
    {
        if(strcmp(ara->sehirAdi,sehir1)==0)
        {
            for(int i=0; i<ara->komsuSayisi; i++)
            {
                if(ara->komsuPlakalar[i]==araSehir(sehir2)->plakaKodu)
                {
                    return 0;
                }
            }
        }
        ara=ara->front;
    }
    if(strcmp(ara->sehirAdi,sehir1)==0)
    {
        for(int i=0; i<ara->komsuSayisi; i++)
        {
            if(ara->komsuPlakalar[i]==araSehir(sehir2)->plakaKodu)
            {
                return 0;
            }
        }
    }
    return 1;
}
void komsulukEkle(char sehir1[],char sehir2[])
{
    struct sehir *ara=cityBAS;
    struct sehir *ara2=cityBAS;
    if(komsuMu(sehir1,sehir2)==0)
    {
        return;
    }
    if(strcmp(sehir1,sehir2)==0)
    {
        return;
    }
    while(ara->front!=cityBAS)
    {
        if(strcmp(ara->sehirAdi,sehir1)==0)
        {
            ara->komsuPlakalar[ara->komsuSayisi]=(int*)malloc(sizeof(int));
            ara->komsuPlakalar[ara->komsuSayisi]=komsuPlakaBul(sehir2);
            ara->komsuSayisi += 1;
            for(int i=0; i<ara->komsuSayisi; i++)
            {
                for(int j=i+1; j<ara->komsuSayisi; j++)
                {
                    if(ara->komsuPlakalar[i]>ara->komsuPlakalar[j])
                    {
                        int temp=ara->komsuPlakalar[i];
                        ara->komsuPlakalar[i]=ara->komsuPlakalar[j];
                        ara->komsuPlakalar[j]=temp;
                    }
                }
            }
        }
        //free(ara->komsuPlakalar);
        ara=ara->front;
    }
    if(strcmp(ara->sehirAdi,sehir1)==0)
    {
        ara->komsuPlakalar[ara->komsuSayisi]=(int*)malloc(sizeof(int));
        ara->komsuPlakalar[ara->komsuSayisi]=komsuPlakaBul(sehir2);
        ara->komsuSayisi += 1;
        for(int i=0; i<ara->komsuSayisi; i++)
        {
            for(int j=i+1; j<ara->komsuSayisi; j++)
            {
                if(ara->komsuPlakalar[i]>ara->komsuPlakalar[j])
                {
                    int temp=ara->komsuPlakalar[i];
                    ara->komsuPlakalar[i]=ara->komsuPlakalar[j];
                    ara->komsuPlakalar[j]=temp;
                }
            }
        }
    }
    while(ara2->front!=cityBAS)
    {
        if(strcmp(ara2->sehirAdi,sehir2)==0)
        {
            ara2->komsuPlakalar[ara2->komsuSayisi]=(int*)malloc(sizeof(int));
            ara2->komsuPlakalar[ara2->komsuSayisi]=komsuPlakaBul(sehir1);
            ara2->komsuSayisi += 1;
            for(int i=0; i<ara2->komsuSayisi; i++)
            {
                for(int j=i+1; j<ara2->komsuSayisi; j++)
                {
                    if(ara2->komsuPlakalar[i]>ara2->komsuPlakalar[j])
                    {
                        int temp=ara2->komsuPlakalar[i];
                        ara2->komsuPlakalar[i]=ara2->komsuPlakalar[j];
                        ara2->komsuPlakalar[j]=temp;
                    }
                }
            }
        }
        //free(ara->komsuPlakalar);
        ara2=ara2->front;
    }
    if(strcmp(ara2->sehirAdi,sehir2)==0)
    {
        ara2->komsuPlakalar[ara2->komsuSayisi]=(int*)malloc(sizeof(int));
        ara2->komsuPlakalar[ara2->komsuSayisi]=komsuPlakaBul(sehir1);
        ara2->komsuSayisi += 1;
        for(int i=0; i<ara2->komsuSayisi; i++)
        {
            for(int j=i+1; j<ara2->komsuSayisi; j++)
            {
                if(ara2->komsuPlakalar[i]>ara2->komsuPlakalar[j])
                {
                    int temp=ara2->komsuPlakalar[i];
                    ara2->komsuPlakalar[i]=ara2->komsuPlakalar[j];
                    ara2->komsuPlakalar[j]=temp;
                }
            }
        }
    }
}

//***************************************************************************
struct sehir *araPlaka(int x)
{
    struct sehir *ara=cityBAS;

    while(ara->front!=cityBAS)
    {
        if(ara->plakaKodu==x)
            return ara;
        ara=ara->front;
    }
    if(ara->plakaKodu==x)
        return ara;

    return NULL;
}
struct sehir *araSehir(char sehir[])
{
    struct sehir *ara=cityBAS;

    while(ara->front!=cityBAS)
    {
        if(strcmp(ara->sehirAdi,sehir)==0)
            return ara;
        ara=ara->front;
    }
    if(strcmp(ara->sehirAdi,sehir)==0)
        return ara;

    return NULL;
}
//***************************************************************************
void komsuBilgileriGosterPlaka(int plaka,int komsuSayisi)
{
    struct sehir *liste=cityBAS;
    while(liste->front!=cityBAS)
    {
        if(liste->plakaKodu==plaka)
        {
            for(int i=0; i<komsuSayisi; i++)
            {
                plakadanBilgiGoster(liste->komsuPlakalar[i]);
            }
            printf("\n");
        }
        liste=liste->front;
    }
    if(liste->plakaKodu==plaka)
    {
        for(int i=0; i<komsuSayisi; i++)
        {
            plakadanBilgiGoster(liste->komsuPlakalar[i]);
        }
        printf("\n");
    }
}
void komsuBilgileriGosterSehir(char sehir[],int komsuSayisi)
{
    struct sehir *liste=cityBAS;
    while(liste->front!=cityBAS)
    {
        if(strcmp(liste->sehirAdi,sehir)==0)
        {
            for(int i=0; i<komsuSayisi; i++)
            {
                plakadanBilgiGoster(liste->komsuPlakalar[i]);
            }
            printf("\n");
        }
        liste=liste->front;
    }
    if(strcmp(liste->sehirAdi,sehir)==0)
    {
        for(int i=0; i<komsuSayisi; i++)
        {
            plakadanBilgiGoster(liste->komsuPlakalar[i]);
        }
        printf("\n");
    }
}
//***************************************************************************
void plakadanBilgiGoster(int plaka)
{
    FILE *ptr2;
    ptr2=fopen("cikti.txt","a");
    struct sehir *liste=cityBAS;
    while(liste->front!=cityBAS)
    {
        if(liste->plakaKodu==plaka)
        {
            printf("%d %s %s\n",liste->plakaKodu,liste->sehirAdi,liste->cografiBolge);
            fprintf(ptr2,"%d %s %s\n",liste->plakaKodu,liste->sehirAdi,liste->cografiBolge);
        }
        liste=liste->front;
    }
    if(liste->plakaKodu==plaka)
    {
        printf("%d %s %s\n",liste->plakaKodu,liste->sehirAdi,liste->cografiBolge);
        fprintf(ptr2,"%d %s %s\n",liste->plakaKodu,liste->sehirAdi,liste->cografiBolge);
    }
}
//***************************************************************************
void sehirSil(int plaka)
{
    struct sehir *sil=cityBAS;
    silinenSehrinKomsuluklariniSil(plaka);
    while(sil!=NULL)
    {
        if(sil->plakaKodu==plaka)
            break;
        else
        {
            sil=sil->front;
        }
    }

    if(sil!=NULL)
    {
        if(sil==cityBAS)
        {
            sil->back->front=sil->front;
            sil->front->back=sil->back;
            cityBAS=cityBAS->front;

        }
        else if(sil==citySON)
        {
            sil->back->front=sil->front;
            sil->front->back=sil->back;
            citySON=citySON->back;
        }
        else
        {
            sil->back->front=sil->front;
            sil->front->back=sil->back;
        }

        free(sil);
    }
}
//***************************************************************************
void silinenSehrinKomsuluklariniSil(int plaka)
{
    struct sehir *liste=cityBAS;
    // struct sehir *listeSON=citySON;
    while(liste->front!=cityBAS)
    {
        if(liste->plakaKodu==plaka)
        {
            for(int i=liste->komsuSayisi-1; i>=0; i--)
            {
                komsulukSil(araPlaka(liste->komsuPlakalar[i])->sehirAdi,liste->sehirAdi);
            }
        }
        liste=liste->front;
    }
    if(liste->plakaKodu==plaka)
    {
        for(int i=liste->komsuSayisi-1; i>=0; i--)
        {
            komsulukSil(araPlaka(liste->komsuPlakalar[i])->sehirAdi,liste->sehirAdi);
        }
    }
}
//***************************************************************************
//***************************************************************************
void komsulukSil(char sehir1[],char sehir2[])
{
    struct sehir *ara=cityBAS;
    struct sehir *ara2=cityBAS;
    while(ara->front!=cityBAS)
    {
        if(strcmp(ara->sehirAdi,sehir1)==0)
        {
            for(int i=0; i<ara->komsuSayisi; i++)
            {

                if(ara->komsuPlakalar[i]==komsuPlakaBul(sehir2))
                {
                    int k=i;
                    //printf("%d\n",ara->komsuPlakalar[i]);
                    //ara->komsuPlakalar[i]=0;
                    while(ara->komsuSayisi >= k)
                    {
                        ara->komsuPlakalar[k]=ara->komsuPlakalar[k+1];
                        k++;
                    }
                }
            }
        }
        //free(ara->komsuPlakalar);
        ara=ara->front;
    }
    if(strcmp(ara->sehirAdi,sehir1)==0)
    {
        for(int i=0; i<ara->komsuSayisi; i++)
        {

            if(ara->komsuPlakalar[i]==komsuPlakaBul(sehir2))
            {
                int k=i;
                //printf("%d\n",ara->komsuPlakalar[i]);
                //ara->komsuPlakalar[i]=0;
                while(ara->komsuSayisi >= k)
                {
                    ara->komsuPlakalar[k]=ara->komsuPlakalar[k+1];
                    k++;
                }
            }
        }
    }
    while(ara2->front!=cityBAS)
    {
        if(strcmp(ara2->sehirAdi,sehir2)==0)
        {
            for(int i=0; i<ara2->komsuSayisi; i++)
            {
                if(ara2->komsuPlakalar[i]==komsuPlakaBul(sehir1))
                {
                    int k=i;
                    while(ara2->komsuSayisi >= k)
                    {
                        ara2->komsuPlakalar[k]=ara2->komsuPlakalar[k+1];
                        k++;
                    }
                }
            }
        }
        //free(ara->komsuPlakalar);
        ara2=ara2->front;
    }
    if(strcmp(ara2->sehirAdi,sehir2)==0)
    {
        for(int i=0; i<ara2->komsuSayisi; i++)
        {
            if(ara2->komsuPlakalar[i]==komsuPlakaBul(sehir1))
            {
                int k=i;
                while(ara2->komsuSayisi >= k)
                {
                    ara2->komsuPlakalar[k]=ara2->komsuPlakalar[k+1];
                    k++;
                }
            }
        }
    }
    komsuSayisiAzalt(sehir1);
    komsuSayisiAzalt(sehir2);
}
//***************************************************************************
void bolgeListele(char bolge[])
{
    FILE *yaz;
    yaz=fopen("cikti.txt","a");
    struct sehir *liste=cityBAS;
    printf("\n%s bolgesindeki sehir listesi:\n",bolge);
    fprintf(yaz,"\n%s bolgesindeki sehir listesi:\n",bolge);
    while(liste->front!=cityBAS)
    {
        if(strcmp(liste->cografiBolge,bolge)==0)
        {
            printf("%d %s Bolge:%s Komsu Sayisi:%d ",liste->plakaKodu,liste->sehirAdi,liste->cografiBolge,liste->komsuSayisi);
            printf("Komsu plakalar:");
            fprintf(yaz,"%d %s Bolge:%s Komsu Sayisi:%d ",liste->plakaKodu,liste->sehirAdi,liste->cografiBolge,liste->komsuSayisi);
            fprintf(yaz,"Komsu plakalar:");
            for(int i=0; i<liste->komsuSayisi; i++)
            {
                printf("->%d",liste->komsuPlakalar[i]);
                fprintf(yaz,"->%d",liste->komsuPlakalar[i]);
            }
            printf("\n");
            fprintf(yaz,"\n");
        }
        liste=liste->front;
    }
    if(strcmp(liste->cografiBolge,bolge)==0)
    {
        printf("%d %s Bolge:%s Komsu Sayisi:%d ",liste->plakaKodu,liste->sehirAdi,liste->cografiBolge,liste->komsuSayisi);
        printf("Komsu plakalar:");
        fprintf(yaz,"%d %s Bolge:%s Komsu Sayisi:%d ",liste->plakaKodu,liste->sehirAdi,liste->cografiBolge,liste->komsuSayisi);
        fprintf(yaz,"Komsu plakalar:");
        for(int i=0; i<liste->komsuSayisi; i++)
        {
            printf("->%d",liste->komsuPlakalar[i]);
            fprintf(yaz,"->%d",liste->komsuPlakalar[i]);
        }
        printf("\n");
        fprintf(yaz,"\n");
    }
}
//***************************************************************************
void degerListele(int x)
{
    FILE *yaz;
    yaz=fopen("cikti.txt","a");
    struct sehir *liste=cityBAS;
    printf("Komsu sayisi %d'den fazla olan sehirler:\n",x);
    fprintf(yaz,"\nKomsu sayisi %d'den fazla olan sehirler:\n",x);
    while(liste->front!=cityBAS)
    {
        if(liste->komsuSayisi>x)
        {
            printf("%d %s Bolge:%s Komsu Sayisi:%d ",liste->plakaKodu,liste->sehirAdi,liste->cografiBolge,liste->komsuSayisi);
            printf("Komsu plakalar:");
            fprintf(yaz,"%d %s Bolge:%s Komsu Sayisi:%d ",liste->plakaKodu,liste->sehirAdi,liste->cografiBolge,liste->komsuSayisi);
            fprintf(yaz,"Komsu plakalar:");

            for(int i=0; i<liste->komsuSayisi; i++)
            {
                printf("->%d",liste->komsuPlakalar[i]);
                fprintf(yaz,"->%d",liste->komsuPlakalar[i]);
            }
            printf("\n");
            fprintf(yaz,"\n");
        }
        liste=liste->front;
    }
    if(liste->komsuSayisi>x)
    {
        printf("%d %s Bolge:%s Komsu Sayisi:%d ",liste->plakaKodu,liste->sehirAdi,liste->cografiBolge,liste->komsuSayisi);
        printf("Komsu plakalar:");
        fprintf(yaz,"%d %s Bolge:%s Komsu Sayisi:%d ",liste->plakaKodu,liste->sehirAdi,liste->cografiBolge,liste->komsuSayisi);
        fprintf(yaz,"Komsu plakalar:");

        for(int i=0; i<liste->komsuSayisi; i++)
        {
            printf("->%d",liste->komsuPlakalar[i]);
            fprintf(yaz,"->%d",liste->komsuPlakalar[i]);
        }
        printf("\n");
        fprintf(yaz,"\n");
    }
}
void komsuSayisiAzalt(char sehir[])
{
    struct sehir *liste=cityBAS;
    while(liste->front!=cityBAS)
    {
        if(strcmp(liste->sehirAdi,sehir)==0)
        {
            liste->komsuSayisi--;
        }
        liste=liste->front;
    }
    if(strcmp(liste->sehirAdi,sehir)==0)
    {
        liste->komsuSayisi--;
    }
}
//***************************************************************************

void Sirala()
{
    char yedekCografiBolge[3];
    int yedekKomsuSayisi;
    char yedekSehirAdi[20];
    int yedekPlakaKodu;
    int *yedekKomsuPlakalar;
    int dizi[20];

    struct sehir *dolas, *adim=cityBAS;
    while(adim!=citySON)
    {
        dolas=cityBAS;
        while(dolas!=citySON)
        {
            if(dolas->plakaKodu > dolas->front->plakaKodu)
            {
                strcpy(yedekCografiBolge,dolas->cografiBolge);
                yedekKomsuSayisi=dolas->komsuSayisi;
                strcpy(yedekSehirAdi,dolas->sehirAdi);
                yedekPlakaKodu=dolas->plakaKodu;
                yedekKomsuPlakalar=dolas->komsuPlakalar;

                strcpy(dolas->cografiBolge,dolas->front->cografiBolge);
                dolas->komsuSayisi=dolas->front->komsuSayisi;
                strcpy(dolas->sehirAdi,dolas->front->sehirAdi);
                dolas->plakaKodu=dolas->front->plakaKodu;
                dolas->komsuPlakalar=dolas->front->komsuPlakalar;

                strcpy(dolas->front->cografiBolge,yedekCografiBolge);
                dolas->front->komsuSayisi=yedekKomsuSayisi;
                strcpy(dolas->front->sehirAdi,yedekSehirAdi);
                dolas->front->plakaKodu=yedekPlakaKodu;
                dolas->front->komsuPlakalar=yedekKomsuPlakalar;

            }
            dolas=dolas->front;
        }
        adim=adim->front;
    }
}
