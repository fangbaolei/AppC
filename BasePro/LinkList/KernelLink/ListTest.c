#include "ListTest.h"

int ListAddNode(ChnInfo ChnHead, char *ChName)
{
    ChnInfo *pChNewNode;
    pChNewNode = (ChnInfo *)malloc(sizeof(ChnInfo));
    memset(pChNewNode,0,sizeof(ChnInfo));
    pChNewNode->name = ChName;
    printf("NodeName:%s\n",pChNewNode->name);
    list_add(&(pChNewNode->list), &ChnHead.list);
    return 0; 
}

int main(void)
{
    ChnInfo Ch;
    ChnInfo *tmp = NULL, *pos = NULL;
    INIT_LIST_HEAD(&Ch.list);
    Ch.name = "abc";
    printf("ch.name:%s\n",Ch.name);
    ListAddNode(Ch,"kkkk"); 
    ListAddNode(Ch,"bbbb"); 
    list_for_each_entry(tmp, &Ch.list, list)
    {
        printf("each node name :%s\n",tmp->name); 
    }
    list_for_each_entry(tmp, &Ch.list, list)
    {
        if(!strcmp(tmp->name,"bbb"))
        {
            
        }
        printf("each node name :%s\n",tmp->name); 
    }
   return 0;
}
