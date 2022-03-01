#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Cache {
    unsigned long csize;
    unsigned long bsize;
    unsigned long sets;
    unsigned long lines;
    unsigned long linesperset;
    char* policy;
    char* type;
    unsigned long*** cachearr;
    unsigned long insertcount;
    unsigned long usecount;
};

int calclog2(unsigned long x){ 
    int y = 0;
    while(x>>=1){
        ++y;
    }
    return y;
}

struct Cache *allocateMemoryForStruct(struct Cache* c) {
    c = (struct Cache *) malloc(sizeof(struct Cache));
    return c;
}

unsigned long*** allocateCacheArray(struct Cache* c) {
    c->cachearr = (unsigned long ***) malloc(sizeof(unsigned **) * c->sets);

    for (int i = 0; i < c->sets; i++) {
        c->cachearr[i] = (unsigned long **) malloc(sizeof (unsigned long *) * c->linesperset);

        for (int j = 0; j < c->linesperset; j++) {
            c->cachearr[i][j] = (unsigned long *) malloc(sizeof(unsigned long) * 5);
        }
    }
    return c->cachearr;
}

unsigned long*** generateCacheArr(struct Cache* c){
    c->cachearr=allocateCacheArray(c);
    for (int i = 0; i < c->sets; i++) { //i = set index
        for (int j = 0; j < c->linesperset; j++) { //j = lines
            for(int k = 0; k<5; k++){ //5 things in here 1. validity bit 2.tag 3.setid 4.insertcount 5.usecount
                c->cachearr[i][j][k]=0; //create empty cache array
            }
        }
    }
    return c->cachearr;
}

struct Cache *initializeCache(struct Cache* c, int csize, int bsize, char *policy, char *type){
    //initialize param
    c=allocateMemoryForStruct(c);
    c->csize = csize;
    c->bsize = bsize;
    c->policy = policy;
    c->type = type;
    c->lines = csize/bsize;
    c->insertcount=-1;
    c->usecount = -1;

    //figuring out lines and sets based on type of cache
    if(strcmp(type, "direct")==0){
        c->sets = c->lines;
        c->linesperset = 1;
    } else if (strcmp(type, "assoc")==0){
        c->sets = 1;
        c->linesperset = c->lines;
    }else {
        int n =  atoi(&type[6]);
        c->sets = csize/(bsize*n);
        c->linesperset = n;
    }

    c->cachearr = NULL;

    c->cachearr = generateCacheArr(c);

    return c;
}

int search(struct Cache *c, unsigned long setid, unsigned long tag, int prefetch ){
    for(int i = 0; i<c->linesperset; i++){
        if(c->cachearr[setid][i][0] == 1 && c->cachearr[setid][i][1]==tag){
            return i; //returns index of line in set where it was found
        }
    }
    return -1;
}

void insert(struct Cache *c, unsigned long setid, unsigned long tag){

    //insert into empty line
    int line=0;
    while (line<c->linesperset){
        if(c->cachearr[setid][line][0]==0){
            c->cachearr[setid][line][0]=1;
            c->cachearr[setid][line][1]=tag;
            c->insertcount++;
            c->usecount++;
            c->cachearr[setid][line][3]=c->insertcount;
            c->cachearr[setid][line][4]=c->usecount;
        }
        line++;
    }

    if(line>=c->linesperset){ //if no empty line use replacement policy
        int replaceline = 0;
        for(int i = 0; i<c->linesperset; i++){
            if(strcmp(c->policy, "fifo") == 0){ //FIFO
                if(c->cachearr[setid][i][3] < c->cachearr[setid][replaceline][3]){
                    replaceline = i;
                }
            }else{ // LRU
                if(c->cachearr[setid][i][4] < c->cachearr[setid][replaceline][4]){
                    replaceline = i;
                }
            }
        }
        c->cachearr[setid][replaceline][1]=tag;
        c->insertcount++;
        c->cachearr[setid][replaceline][3]=c->insertcount;
        c->usecount++;
        c->cachearr[setid][replaceline][4]=c->usecount;
    }
    return;
}

void read(struct Cache *c, unsigned long setid, unsigned long tag, int*mr, int*mw, int*ch, int*cm){

    int found = search(c, setid, tag,-1);

    if(found == -1){
        insert(c, setid, tag);
        (*cm)++;
        (*mr)++;
    }else{
        (*ch)++;
        c->usecount++;
        c->cachearr[setid][found][4]=c->usecount;
    }

    return;
}

void pread(struct Cache *c, unsigned long setid, unsigned long tag, unsigned long blockid,
           int sbit, unsigned long setmask, int*mr, int*mw, int*ch, int*cm){

    int found = search(c, setid, tag,0);

    if(found == -1){
        insert(c, setid, tag);
        (*cm)++;
        (*mr)++;

        unsigned long newblockid = blockid+1;
        unsigned long newsetid=newblockid&setmask;
        unsigned long newtag=newblockid>>sbit;

        int found2 = search(c, newsetid, newtag,0);
        if(found2==-1){
            (*mr)++;
            insert(c, newsetid, newtag);
        }
    }else{
        (*ch)++;
        c->usecount++;
        c->cachearr[setid][found][4]=c->usecount;
    }

    return;
}

void write(struct Cache *c, unsigned long setid, unsigned long tag, int*mr, int*mw, int*ch, int*cm){

    int found = search(c, setid, tag,-1);

    if (found ==-1){
        insert(c, setid, tag);
        (*cm)++;
        (*mw)++;
        (*mr)++;

    }else{
        (*ch)++;
        (*mw)++;
        c->usecount++;
        c->cachearr[setid][found][4]=c->usecount;
    }
    return;
    
}

void pwrite(struct Cache *c, unsigned long setid, unsigned long tag, unsigned long blockid, int sbit, unsigned long setmask, int*mr, int*mw, int*ch, int*cm){

    int found = search(c, setid, tag,0);
    (*mw)++;

    if(found == -1){
        insert(c, setid, tag);
        (*cm)++;
        (*mr)++;

        unsigned long newblockid = blockid+1;
        unsigned long newsetid=newblockid&setmask;
        unsigned long newtag=newblockid>>sbit;

        int found2 = search(c, newsetid, newtag,0);

        if(found2==-1){
            (*mr)++;
            insert(c, newsetid, newtag);
        }
    }else{
        (*ch)++;
        c->usecount++;
        c->cachearr[setid][found][4]=c->usecount;
        
    }

    return;
}

int main(int argc, char *argv[]){
    //read params
    int csize = atoi(argv[1]);
    char* type = argv[2];
    char* policy = argv[3];
    int bsize = atoi(argv[4]);

    //initialize pcache and cache
    struct Cache* cache = NULL;
    cache = initializeCache(cache, csize, bsize, policy, type);
    struct Cache* pcache = NULL;
    pcache = initializeCache(pcache, csize, bsize, policy, type);

    //no prefetch var
    int p = 0;
    int mr = 0;
    int mw = 0;
    int ch = 0;
    int cm = 0;

    //prefetch var
    int pp = 1;
    int pmr = 0;
    int pmw = 0;
    int pch = 0;
    int pcm = 0;

    int bbit = calclog2(bsize);
    int sbit = calclog2(cache->sets); //ok to use only cache bc at this point cache and pcache are the same
    unsigned long setmask = (1<<sbit)-1;

    //process file
    FILE *trace = fopen(argv[5],"r");
    char command;
    unsigned long address;
    char garbage[100];
    while (fscanf(trace, "%75s", garbage) != EOF){

        if (strcmp(garbage, "#eof")==0) {
            break;
        }

        fscanf(trace, " %c %lx", &command, &address);

        unsigned long blockid = address>>bbit; //remove block offset
        unsigned long setid=blockid&setmask;
        unsigned long tag=blockid>>sbit;

        if(command == 'R'){
            read(cache, setid, tag, &mr, &mw, &ch, &cm);
            pread(pcache, setid, tag, blockid, sbit, setmask, &pmr, &pmw, &pch, &pcm);
        }else if(command == 'W'){
            write(cache, setid, tag, &mr, &mw, &ch, &cm);
            pwrite(pcache, setid, tag, blockid, sbit, setmask, &pmr, &pmw, &pch, &pcm);
        }
    }

    //print no prefetch result
    printf("Prefetch %d\n", p);
    printf("Memory reads: %d\n", mr);
    printf("Memory writes: %d\n", mw);
    printf("Cache hits: %d\n", ch);
    printf("Cache misses: %d\n", cm);

    //print prefetch results
    printf("Prefetch %d\n", pp);
    printf("Memory reads: %d\n", pmr);
    printf("Memory writes: %d\n", pmw);
    printf("Cache hits: %d\n", pch);
    printf("Cache misses: %d\n", pcm);

    //free everything sis
    for (int i = 0; i < cache->sets; i++) {
        for (int j = 0; j < cache->linesperset; j++) {
            free(cache->cachearr[i][j]);
        }
    }
    for (int i = 0; i < cache->sets; i++) {
        free(cache->cachearr[i]);
    }
    free(cache->cachearr);

    for (int i = 0; i < pcache->sets; i++) {
        for (int j = 0; j < pcache->linesperset; j++) {
            free(pcache->cachearr[i][j]);
        }
    }
    for (int i = 0; i < cache->sets; i++) {
        free(pcache->cachearr[i]);
    }
    free(pcache->cachearr);

    free(cache);
    free(pcache);

    return 0;
}