#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED


int loadFromtText(LinkedList* lista, int* flagYaSeCargo);
int saveAsText(char* path, LinkedList* lista);
int parser_FromTxt(FILE* pFile, LinkedList* lista);

#endif // PARSER_H_INCLUDED
