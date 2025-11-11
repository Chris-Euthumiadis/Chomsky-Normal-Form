#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dexia // vlepe eikona
{   char *str;
    struct dexia *next;
};

char V[]={'S','A','B','a','b'};  // exei mesa ta kefalaia kai ta mikra tis grammatikis (gia elegxo egkirotitas)
char alphavito[]={'a','b'};  // exei mesa mono ta mikra tis grammatikis (gia elegxo egkirotitas)
char **aristera;
struct dexia **head,**tail;
struct dexia *svismena_e_head=NULL, *svismena_e_tail=NULL, *svismenoi_kanones_head=NULL, *svismenoi_kanones_tail=NULL;
int grammes_arxeiou, temp_grammes_arxeiou;

int diagrafi_protis_emfanisis_xaraktira(char *str, char ch, int starting)
{
    int i, thesi;
    long int len; // to evala egw
    
    len = strlen(str);
    
    for(i = starting; i < len && str[i] != ch; i++);
    
    thesi = i;
    while(i < len)
    {
        str[i] = str[i + 1];
        i++;
    }
    return thesi;
}

void svino_ton_kanona_me_e(struct dexia *temp, int i, char *str)
{
    struct dexia *before = NULL;
    struct dexia *current = head[i];
    
    // psaxno na vro poy einai to "e" (orisma: temp)
    while(current != NULL)
    {   if (current == temp) {
        break;
    }
    else {
        before = current;
        current = current->next;
    }
        //printf("POSO\n");
    }
    
    // afou to vro, enono to proigoumeno me to epomeno (ara to svino)
    if (before != NULL)
    {   before->next=current->next;
        if (current->next==NULL)
            tail[i]=before;
    }
    else
    {   head[i]=current->next;
        if (current->next==NULL)
            tail[i]=NULL;
    }
    
    //temp = (struct dexia *) malloc(sizeof(struct dexia));
    //temp->str = (char *) malloc(20 * sizeof(char ));
    
    // sti lista "svismena_e" einai ta kefalaia pou exoyn svistei kai eixan "e" sta dexia
    // (ara vazo to kefalaio pou molis esvisa)
    strcpy(current->str,str);
    current->next=NULL;
    if (svismena_e_head == NULL) {
        svismena_e_head = current;
        svismena_e_tail = current;
    }
    else {
        svismena_e_tail->next = current;
        svismena_e_tail = current;
    }
    
    //printf("FREE\n");
    return;
}

void svino_ton_kanona_me_ena_kefalaio(struct dexia *temp, int i,char *str,int flag)
{
    struct dexia *before = NULL;
    struct dexia *current = head[i];
    
    while(current != NULL)
    {   if (current == temp) {
        break;
    }
    else {
        before = current;
        current = current->next;
    }
        //printf("POSO222\n");
    }
    
    if (before != NULL)
    {   before->next=current->next;
        if (current->next==NULL)
            tail[i]=before;
    }
    else
    {   head[i]=current->next;
        if (current->next==NULL)
            tail[i]=NULL;
    }
    
    //temp = (struct dexia *) malloc(sizeof(struct dexia));
    //temp->str = (char *) malloc(20 * sizeof(char ));
    if (flag==1) {
        strcpy(current->str,str);
        current->next=NULL;
        if (svismenoi_kanones_head == NULL) {
            svismenoi_kanones_head = current;
            svismenoi_kanones_tail = current;
        }
        else {
            svismenoi_kanones_tail->next = current;
            svismenoi_kanones_tail = current;
        }
    }
    else {
        free(current);
    }
    
    //printf("FREE222\n");
    return;
}

void svino_ton_kanona_vima4(struct dexia *temp, int i)
{
    struct dexia *before = NULL;
    struct dexia *current = head[i];
    
    while(current != NULL)
    {   if (current == temp) {
        break;
    }
    else {
        before = current;
        current = current->next;
    }
        //printf("POSO\n");
    }
    
    if (before != NULL)
    {   before->next=current->next;
        if (current->next==NULL)
            tail[i]=before;
    }
    else
    {   head[i]=current->next;
        if (current->next==NULL)
            tail[i]=NULL;
    }
    
    free(current);
}

int psakse_an_yparxei_svismeno_e(char *str)
{   struct dexia *temp;
    
    temp = svismena_e_head;
    while (temp != NULL) {
        //printf("MIPOS %s,%s,\n",temp->str,str);
        if (strcmp(temp->str,str) == 0 ) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

int psakse_an_yparxei_svismenos_kanonas(char *str)
{   struct dexia *temp;
    
    temp = svismenoi_kanones_head;
    while (temp != NULL) {
        //printf("MIPOS222 %s,%s,\n",temp->str,str);
        if (strcmp(temp->str,str) == 0 ) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

int psakse_an_yparxei_idi_periptosi(char *str, int i)
{   struct dexia *temp;
    
    temp = head[i];
    while (temp != NULL) {
        if (strcmp(temp->str,str) == 0 ) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

void vres_dexia_kai_antikatestise_me_keno(char c)
{ int i,x,prosthiki_neas_periptosis, thesi, starting;
    struct dexia *temp, *new_case;
    char *check = (char *) malloc(20 * sizeof(char ));
    
    for (i=0;i<grammes_arxeiou;i++) { // se ola ta dexia kommatia psaxno to kefalaio (orisma: c) an yparxei
        temp=head[i];
        while (temp != NULL) {
            if (strchr(temp->str,c) != NULL ) { // an vro to kefalaio kapou dexia
                if (strlen(temp->str)==1) {  // an sta "dexia" einai ena kefalaio mono tou
                    //printf("MPIKE MONO\n");
                    x = psakse_an_yparxei_svismeno_e(aristera[i]); // an exei svistei NWRITERA to kefalaio, epistrefei 1
                    //printf("To MONO x einai %d\n",x);
                    //system("pause");
                    if (x==0) {  // den exei svistei NWRITERA, tote vazo opou einai to kefalaio (orisma: c) to "e"
                        new_case = (struct dexia *) malloc(sizeof(struct dexia));
                        new_case->str = (char *) malloc(20 * sizeof(char ));
                        strcpy(new_case->str,"e");
                        new_case->next=NULL;
                        tail[i]->next = new_case;
                        tail[i] = new_case;
                    }
                }
                else {  // an sta "dexia" einai polla kefalaia h' esto me mikro gramma
                    //printf("MPIKE POLLAPLO\n");
                    prosthiki_neas_periptosis=1;
                    strcpy(check,temp->str);
                    starting=0;
                    while(prosthiki_neas_periptosis==1) {
                        thesi = diagrafi_protis_emfanisis_xaraktira(check,c,starting);
                        if (thesi == strlen(temp->str)) { // an teleiose to deksi kommati pou eixe mesa to kefalaio
                            //printf("RE\n");
                            //system("pause");
                            prosthiki_neas_periptosis=0;
                        }
                        else {
                            // Otan einai sta dexia polles fores to kefalaio pou tha valo "e" p.x. S -> ASA tote an sto A valw "e", prepei na parw sindiasmous.
                            // Opote gia na min parw polles fores ton idio sindiasmo, elegxo me tin "psakse_an_yparxei_idi_periptosi" an yparxei idi (tote den to ksanavazo)
                            x = psakse_an_yparxei_idi_periptosi(check,i); // ayto poy esteile sto MAIL
                            //printf("To POLLAPLO x einai %d\n",x);
                            //system("pause");
                            if (x==0) {
                                new_case = (struct dexia *) malloc(sizeof(struct dexia));
                                new_case->str = (char *) malloc(20 * sizeof(char ));
                                strcpy(new_case->str,check);
                                new_case->next=NULL;
                                tail[i]->next = new_case;
                                tail[i] = new_case;
                            }
                            strcpy(check,temp->str);
                            starting=thesi+1;
                        }
                    }
                }
            }
            temp = temp->next;
        }
    }
    //printf("Antikatestise\n");
}

void print_kanones(void)
{   int i;
    struct dexia *temp;
    
    for (i=0;i<grammes_arxeiou;i++) {
        temp=head[i];
        if (temp != NULL) {
            printf("%s -> %s", aristera[i], temp->str);
            while (temp->next != NULL) {
                temp=temp->next;
                printf(" | %s",temp->str);
            }
            printf("\n");
        }
    }
    printf("\n\n\n");
    
}

void vres_dexia_kai_antikatestise_me_kanones(char *str, int k)
{ int i, x;
    struct dexia *temp, *new_case;
    char *s;
    
    
    for (i=0;i<grammes_arxeiou;i++) {
        if (strcmp(aristera[i],str) == 0 ) {
            temp=head[i];
            
            while (temp != NULL) {
                if (strlen(temp->str) == 1 && strstr(V,temp->str) != NULL && strstr(alphavito,temp->str) == NULL) {
                    s = (char *) malloc(20 * sizeof(char ));
                    strcpy(s,aristera[k]);
                    strcat(s,temp->str);
                    x = psakse_an_yparxei_svismenos_kanonas(s);
                    //printf("EM %s,%d,\n",s,x);
                    //system("pause");
                    if (x == 0) {
                        new_case = (struct dexia *) malloc(sizeof(struct dexia));
                        new_case->str = (char *) malloc(20 * sizeof(char ));
                        strcpy(new_case->str,temp->str);
                        new_case->next=NULL;
                        tail[k]->next = new_case;
                        tail[k] = new_case;
                    }
                }
                else {
                    new_case = (struct dexia *) malloc(sizeof(struct dexia));
                    new_case->str = (char *) malloc(20 * sizeof(char ));
                    strcpy(new_case->str,temp->str);
                    new_case->next=NULL;
                    tail[k]->next = new_case;
                    tail[k] = new_case;
                }
                temp = temp->next;
            }
            break;
        }
    }
    //printf("Antikatestise222\n");
    
}

int main()
{   FILE *infile,*outfile;
    int position, i, j, changed, grammi_arxeiou, plithos_kanonon, elegxos_e_dexia, elegxos_kefalaio_dexia, u_number, u_number_before = 0;
    long int c, ypoloipo_mikos; // to evala egw = 0
    struct dexia *temp, *temp_u, *temp_next;
    
    aristera = (char **) malloc(100 * sizeof(char *));  // theorisa oti aristera mexri 100 kefalaia (ara 100 grammes)
    head = (struct dexia **) malloc(100* sizeof(struct dexia *));
    tail = (struct dexia **) malloc(100* sizeof(struct dexia *));
    
    //printf("%s\n", V);
    char buf[81];
    char *p, tokens[]="| \n";
    char *s,*w1,*w2,*w;
    
    if ((infile = fopen("eisodos.txt", "r"))==NULL) {  // anoigei to arxeio mesa sto opoio einai h grammatiki (kanones)
        printf("Den anoixe to arxeio\n");
        exit(1);
    }
    p = (char *) malloc(81 * sizeof(char));
    grammi_arxeiou=0; // trexousa grammi pou vriskomai sto arxeio
    while (fgets(buf, 81, infile) != NULL) {  // i grammi apothikevetai se ena pinaka "buf" (max 81)
        //printf("%s\n", buf);
        c = strlen(buf);
        //printf("%d\n", c);
        p = strtok(buf, tokens); //xorizei to "buf" me diaxoristika opou vriskei | h' keno h' allagi grammis
        position = 0;  // metritis tou kommatioy poy vrike h strtok
        while (p) { // oso vriskei kommatia sinexizei
            //printf("%s\n", p);
            //printf("%d\n", strlen(p));
            if (position == 0) {  // ara thelo to kefalaio aristera
                if (strstr(V,p) == NULL || strstr(alphavito,p) != NULL) {  // an to kommati den anikei sto V H' to kommati einai mikro
                    printf("O kanonas aristera exei kefalaio pou den anikei sto V h' einai mikro.\n");
                    exit(1);
                }
                aristera[grammi_arxeiou] = (char *) malloc(5 * sizeof(char));  // max 5 grammata (an thelei kai deikti p.x. S1)
                strcpy(aristera[grammi_arxeiou],p);   // apothikevo sto "aristera" to kommati
            }
            else if (position == 1) { // einai to kommati "->"
                if (strcmp("->",p) != 0) { // an to kommati den einai to "->"
                    printf("O kanonas sti mesi den exei to ->.\n");
                    exit(1);
                }
            }
            else { // ena kommati sta dexia (meta to velaki)
                if (strcmp("e",p) != 0) {  // ektos an einai keno "e"
                    for (i=0;i<strlen(p);i++) {  // elegxei an sto kommati ta kefalaia kai ta mikra anikoun sto V
                        //printf("Stoixeio %c \n", p[i]);
                        if (strchr(V,p[i]) == NULL ) {
                            printf("O kanonas sta dexia exei simvolo %s pou den anikei sto V.\n", p);
                            exit(1);
                        }
                    }
                }
                // ftiaxno "struct dexia" na apothikefso to kommati
                temp = (struct dexia *) malloc(sizeof(struct dexia));
                temp->str = (char *) malloc(20 * sizeof(char ));
                strcpy(temp->str,p);
                temp->next = NULL;
                // to vazo sti lista head-tail (vlepe sxima)
                if (position==2) // mpainei to prwto apo ta dexia
                {   head[grammi_arxeiou] = temp;
                    tail[grammi_arxeiou] = temp;
                }
                else  // mpainoun ta ypoloipa apo ta dexia
                {
                    tail[grammi_arxeiou]->next = temp;
                    tail[grammi_arxeiou] = temp;
                }
                //printf("MMM\n");
            }
            position++; // epomeno kommati
            p = strtok(NULL, tokens); // paw sto epomeno
            //printf("GGG\n");
        }
        grammi_arxeiou++; // epomeni grammi
        //printf("KKK\n");
    }
    //printf("aaa\n");
    //fclose(infile);
    // printf("LLL\n");
    
    
    //1. Vazo ton kanona S0-> S
    aristera[grammi_arxeiou] = (char *) malloc(5 * sizeof(char));
    strcpy(aristera[grammi_arxeiou],"S0");
    temp = (struct dexia *) malloc(sizeof(struct dexia));
    temp->str = (char *) malloc(20 * sizeof(char ));
    strcpy(temp->str,"S");
    temp->next = NULL;
    head[grammi_arxeiou] = temp;
    tail[grammi_arxeiou] = temp;
    grammi_arxeiou++;
    
    grammes_arxeiou=grammi_arxeiou;
    plithos_kanonon = grammes_arxeiou;
    //printf("%d\n", plithos_kanonon);
    
    //print_kanones();
    
    //2. Svino tous kanones me "e" sta dexia
    elegxos_e_dexia=1;  // otan ginei mellontika 0, simainei oti svistikan oloi oi kanones me "e" sta dexia
    while(elegxos_e_dexia==1) {
        elegxos_e_dexia=0;  // to kanw 0 (wstoso parakatw mporei na ksanaginei 1)
        for (i=0;i<grammes_arxeiou;i++) {  // psaxno na vro an yparxei kanonas me "e" sta dexia (sximatika) ksekinontas apo tin prwti grammi
            temp=head[i];
            while (temp != NULL) {
                if (strcmp("e",temp->str) == 0 && strcmp(aristera[i],"S0") != 0) { // an vrei "e" sta dexia kai den einai S0 -> e (epitrepetai mono to S0 -> e)
                    //printf("VRIKE %s\n",aristera[i]);
                    //system("pause");
                    svino_ton_kanona_me_e(temp,i,aristera[i]);  // kalw ti sinartisi "svino_ton_kanona_me_e"
                    vres_dexia_kai_antikatestise_me_keno(aristera[i][0]); // kalw ti sinartisi "vres_dexia_kai_antikatestise_me_keno" gia na vrei kanones pou exoun dexia to kefalaio (poy esvisa to "e") kai na valw "e"
                    elegxos_e_dexia=1;
                    break;
                }
                temp=temp->next;
            }
            if (elegxos_e_dexia==1)
                break;
        }
        //print_kanones();
        //system("pause");
    }
    
    //print_kanones();
    
    //3. Svino tous kanones me "mono ena kefalaio" sta dexia
    elegxos_kefalaio_dexia=1;
    while(elegxos_kefalaio_dexia==1) {
        elegxos_kefalaio_dexia=0;
        for (i=0;i<grammes_arxeiou;i++) {
            temp=head[i];
            while (temp != NULL) {
                if (strlen(temp->str) == 1 && strstr(V,temp->str) != NULL && strstr(alphavito,temp->str) == NULL) {
                    //printf("VRIKE %s%s\n",aristera[i],temp->str);
                    
                    s = (char *) malloc(20 * sizeof(char ));
                    strcpy(s,aristera[i]);
                    strcat(s,temp->str);
                    if (strcmp(aristera[i],temp->str) != 0 ) { // Χ -> Υ opoy X,Y diaforetika kefalaia
                        if (psakse_an_yparxei_svismenos_kanonas(s) == 0) {
                            vres_dexia_kai_antikatestise_me_kanones(temp->str, i);
                            svino_ton_kanona_me_ena_kefalaio(temp,i,s,1);
                        }
                        else {
                            svino_ton_kanona_me_ena_kefalaio(temp,i,s,2);
                        }
                    }
                    else { // Χ -> Υ opoy X=Y (p.x. S -> S) tote apla svino ton kanona
                        if (psakse_an_yparxei_svismenos_kanonas(s) == 0) {
                            svino_ton_kanona_me_ena_kefalaio(temp,i,s,1);
                        }
                        else {
                            svino_ton_kanona_me_ena_kefalaio(temp,i,s,2);
                        }
                    }
                    
                    elegxos_kefalaio_dexia=1;
                    break;
                }
                temp=temp->next;
            }
            if (elegxos_kefalaio_dexia==1)
                break;
        }
        //print_kanones();
        //system("pause");
    }
    
    //print_kanones();
    
    //4. Metatrepo tous kanones: eite me "dyo kefalaia" sta dexia, eite me "ena mikro" sta dexia
    u_number = 1;
    temp_grammes_arxeiou=grammes_arxeiou;
    for (i=0;i<temp_grammes_arxeiou;i++) {
        temp=head[i];
        while (temp != NULL) {
            temp_next = temp->next;
            changed = 0;
            for (j=0;j<strlen(temp->str);j++) {
                if ( strchr(alphavito,temp->str[j] ) != NULL ) {
                    changed=1;
                }
            }
            //printf("TEL %d,%d,%d,\n",temp_grammes_arxeiou, changed, strlen(temp->str));
            //system("pause");
            
            j=0;
            if (strlen(temp->str) >= 3 && strchr(temp->str,'U') == NULL) { // toylaxiston 3 xaraktires
                
                ypoloipo_mikos=strlen(temp->str);
                while (ypoloipo_mikos>2) {
                    w1 = (char *) malloc(2 * sizeof(char ));
                    if ( strchr(alphavito,temp->str[j]) != NULL ) {
                        sprintf(w1, "U%d", u_number);
                        temp_u = (struct dexia *) malloc(sizeof(struct dexia));
                        temp_u->str = (char *) malloc(20 * sizeof(char ));
                        strncpy(temp_u->str,temp->str + j,1);
                        temp_u->next = NULL;
                        aristera[grammes_arxeiou] = (char *) malloc(5 * sizeof(char));
                        strcpy(aristera[grammes_arxeiou],w1);
                        head[grammes_arxeiou] = temp_u;
                        tail[grammes_arxeiou] = temp_u;
                        grammes_arxeiou++;
                        u_number++;
                    }
                    else {
                        sprintf(w1, "%c", temp->str[j]);
                    }
                    
                    w2 = (char *) malloc(2 * sizeof(char ));
                    sprintf(w2, "U%d", u_number);
                    u_number++;
                    
                    w = (char *) malloc((strlen(w1)+strlen(w2)) * sizeof(char ));
                    strcpy(w,w1);
                    strcat(w,w2);
                    temp_u = (struct dexia *) malloc(sizeof(struct dexia));
                    temp_u->str = (char *) malloc(20 * sizeof(char ));
                    strcpy(temp_u->str,w);
                    temp_u->next = NULL;
                    if (j==0) {
                        tail[i]->next = temp_u;
                        tail[i] = temp_u;
                        u_number_before=u_number-1;
                    }
                    else {
                        aristera[grammes_arxeiou] = (char *) malloc(5 * sizeof(char));
                        sprintf(aristera[grammes_arxeiou], "U%d", u_number_before);
                        head[grammes_arxeiou] = temp_u;
                        tail[grammes_arxeiou] = temp_u;
                        grammes_arxeiou++;
                        u_number_before=u_number-1;
                    }
                    j++;
                    ypoloipo_mikos--;
                    //printf("TEL_MESA %s,\n",w);
                    //system("pause");
                }
                w1 = (char *) malloc(2 * sizeof(char ));
                if ( strchr(alphavito,temp->str[j]) != NULL ) {
                    sprintf(w1, "U%d", u_number);
                    temp_u = (struct dexia *) malloc(sizeof(struct dexia));
                    temp_u->str = (char *) malloc(20 * sizeof(char ));
                    strncpy(temp_u->str,temp->str + j,1);
                    temp_u->next = NULL;
                    aristera[grammes_arxeiou] = (char *) malloc(5 * sizeof(char));
                    strcpy(aristera[grammes_arxeiou],w1);
                    head[grammes_arxeiou] = temp_u;
                    tail[grammes_arxeiou] = temp_u;
                    grammes_arxeiou++;
                    u_number++;
                }
                else {
                    sprintf(w1, "%c", temp->str[j]);
                }
                
                w2 = (char *) malloc(2 * sizeof(char ));
                if ( strchr(alphavito,temp->str[j+1]) != NULL ) {
                    sprintf(w2, "U%d", u_number);
                    temp_u = (struct dexia *) malloc(sizeof(struct dexia));
                    temp_u->str = (char *) malloc(20 * sizeof(char ));
                    strncpy(temp_u->str,temp->str + j+1,1);
                    temp_u->next = NULL;
                    aristera[grammes_arxeiou] = (char *) malloc(5 * sizeof(char));
                    strcpy(aristera[grammes_arxeiou],w2);
                    head[grammes_arxeiou] = temp_u;
                    tail[grammes_arxeiou] = temp_u;
                    grammes_arxeiou++;
                    u_number++;
                }
                else {
                    sprintf(w2, "%c", temp->str[j+1]);
                }
                
                w = (char *) malloc((strlen(w1)+strlen(w2)) * sizeof(char ));
                strcpy(w,w1);
                strcat(w,w2);
                temp_u = (struct dexia *) malloc(sizeof(struct dexia));
                temp_u->str = (char *) malloc(20 * sizeof(char ));
                strcpy(temp_u->str,w);
                temp_u->next = NULL;
                aristera[grammes_arxeiou] = (char *) malloc(5 * sizeof(char));
                sprintf(aristera[grammes_arxeiou], "U%d", u_number_before);
                head[grammes_arxeiou] = temp_u;
                tail[grammes_arxeiou] = temp_u;
                grammes_arxeiou++;
                //printf("TEL_VGAINEI %s,\n",w);
                svino_ton_kanona_vima4(temp,i);
                //print_kanones();
                //system("pause");
            }
            else if (strlen(temp->str) == 2 && changed==1) { // akrivws 2 xaraktires kai yparxei ena mikro
                w1 = (char *) malloc(2 * sizeof(char ));
                if ( strchr(alphavito,temp->str[j]) != NULL ) {
                    sprintf(w1, "U%d", u_number);
                    temp_u = (struct dexia *) malloc(sizeof(struct dexia));
                    temp_u->str = (char *) malloc(20 * sizeof(char ));
                    strncpy(temp_u->str,temp->str + j,1);
                    temp_u->next = NULL;
                    aristera[grammes_arxeiou] = (char *) malloc(5 * sizeof(char));
                    strcpy(aristera[grammes_arxeiou],w1);
                    head[grammes_arxeiou] = temp_u;
                    tail[grammes_arxeiou] = temp_u;
                    grammes_arxeiou++;
                    u_number++;
                }
                else {
                    sprintf(w1, "%c", temp->str[j]);
                }
                
                w2 = (char *) malloc(2 * sizeof(char ));
                if ( strchr(alphavito,temp->str[j+1]) != NULL ) {
                    sprintf(w2, "U%d", u_number);
                    temp_u = (struct dexia *) malloc(sizeof(struct dexia));
                    temp_u->str = (char *) malloc(20 * sizeof(char ));
                    strncpy(temp_u->str,temp->str + j+1,1);
                    temp_u->next = NULL;
                    aristera[grammes_arxeiou] = (char *) malloc(5 * sizeof(char));
                    strcpy(aristera[grammes_arxeiou],w2);
                    head[grammes_arxeiou] = temp_u;
                    tail[grammes_arxeiou] = temp_u;
                    grammes_arxeiou++;
                    u_number++;
                }
                else {
                    sprintf(w2, "%c", temp->str[j+1]);
                }
                
                w = (char *) malloc((strlen(w1)+strlen(w2)) * sizeof(char ));
                strcpy(w,w1);
                strcat(w,w2);
                temp_u = (struct dexia *) malloc(sizeof(struct dexia));
                temp_u->str = (char *) malloc(20 * sizeof(char ));
                strcpy(temp_u->str,w);
                temp_u->next = NULL;
                tail[i]->next = temp_u;
                tail[i] = temp_u;
                //printf("TEL_VGAINEI %s,\n",w);
                svino_ton_kanona_vima4(temp,i);
                //print_kanones();
                //system("pause");
            }
            temp = temp_next;
        }
    }
    print_kanones();
    
    // Apothikeusi neon kanonon sto "output.txt"
    if ((outfile = fopen("eksodos.txt", "w"))==NULL) {
        printf("Den anoixe to arxeio\n");
        exit(1);
    }
    for (i=0;i<grammes_arxeiou;i++) {
        temp=head[i];
        if (temp != NULL) {
            fprintf(outfile,"%s -> %s", aristera[i], temp->str);
            while (temp->next != NULL) {
                temp=temp->next;
                fprintf(outfile," | %s",temp->str);
            }
            fprintf(outfile,"\n");
        }
    }
}

