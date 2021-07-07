#define ERROR -1
#define ALLOK 1

int getInt(int *pResultado,
           char *pMensaje,
           char *pMensajeError,
           int minimo,
           int maximo,
           int reintentos);

float getFloat(float *pResultado,
               char *pMensaje,
               char *pMensajeError,
               float minimo,
               float maximo,
               int reintentos);

char getChar(char *pResultado,
             char *pMensaje,
             char *pMensajeError,
             char minimo,
             char maximo,
             int reintentos);

int getString(char *pResultado,
              char *pMensaje,
              char *pMensajeError,
              int minimo,
              int maximo,
              int reintentos);

int getNombreOApellido(char *pResultado,
                       char *pMensaje,
                       char *pMensajeError,
                       int minimo,
                       int maximo,
                       int reintentos);

int getStringTelefono(char *pResultado,
                      char *pMensaje,
                      char *pMensajeError,
                      int minimo,
                      int maximo,
                      int reintentos);

char getSexo(char *pResultado,char *pMensaje,char *pMensajeError,int reintentos);

int esNumerico(char str[]);
int esTelefono(char str[]);
int esAlfanumerico(char str[]);
int esSoloLetras(char str[]);

int isValidNombre(char* cadena,int longitud);
void convertirMayuscula(char* cadena);
void convertirMinuscula(char* cadena);
