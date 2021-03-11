#include "groupsDB.h"

int main()
{
    char ip[MAX_NUM_OF_GROUP];
    char *groupNames[MAX_NUM_OF_GROUP];
    int i, size;
    
    groupsDB *grp = GroupsDBCreate();
    printf("%d %s\n", GroupsDBOpenNewGroup(grp, "HELLO", "noa", ip), ip);
    printf("%d %s\n", GroupsDBOpenNewGroup(grp, "???", "noa", ip), ip);
    printf("%d\n", GroupsDBOpenNewGroup(grp, "HELLO", "noa", ip));
    printf("%d\n", GroupsDBOpenNewGroup(grp, "", "noa", ip));
    printf("%d %s\n", GroupsDBAddClientToGroup(grp, "HELLO", "maayan", ip), ip);
    printf("%d\n", GroupsDBAddClientToGroup(grp, "NOTEXIST", "maayan", ip));
    printf("%d\n", GroupsDBAddClientToGroup(grp, "", "maayan", ip));
    printf("%u\n", (size = GroupsDBGetGroupNames(grp, groupNames)));
    for(i=0; i<size; ++i)
    {
        printf("%s\n", groupNames[i]);
    }
    printf("%d\n", GroupsDBRemoveClientFromGroup(grp, "HELLO", "noa"));
    printf("%d\n", GroupsDBRemoveClientFromGroup(grp, "HELLO", "ron"));
    printf("%d\n", GroupsDBRemoveClientFromGroup(grp, "???", "noa"));
    printf("%u\n", (size = GroupsDBGetGroupNames(grp, groupNames)));
    for(i=0; i<size; ++i)
    {
        printf("%s\n", groupNames[i]);
    }
    GroupsDBDestroy(grp);
    
    return 0;
}
