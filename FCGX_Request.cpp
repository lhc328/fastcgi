typedef struct FCGX_Request {
    int requestId;            /* valid if isBeginProcessed */
    int role;
    FCGX_Stream *in;     //标准输入 
    FCGX_Stream *out;   //标准输出
    FCGX_Stream *err;   //标准错误
    char **envp;   //环境变量

    /* Don't use anything below here */

    struct Params *paramsPtr;
    int ipcFd;               /* < 0 means no connection */
    int isBeginProcessed;     /* FCGI_BEGIN_REQUEST seen */
    int keepConnection;       /* don't close ipcFd at end of request */
    int appStatus;
    int nWriters;             /* number of open writers (0..2) */
    int flags;
    int listen_sock;
    int detached;
} FCGX_Request;

//作者：温暖春阳
//链接：https://www.jianshu.com/p/79f8975ea90d
//來源：简书
