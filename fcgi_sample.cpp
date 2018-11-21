/*
 * threaded.c -- A simple multi-threaded FastCGI application.
 */

#ifndef lint
static const char rcsid[] = "$Id: threaded.c,v 1.9 2001/11/20 03:23:21 robs Exp $";
#endif /* not lint */

#include "fcgi_config.h"

#include <pthread.h>
#include <sys/types.h>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#include "fcgiapp.h"


#define THREAD_COUNT 20

static int counts[THREAD_COUNT];

static void *doit(void *a)
{
    int rc, i, thread_id = (int)a;
    pid_t pid = getpid();
    FCGX_Request request;  //定义一个request变量，包含了输入输出。
    char *server_name;

    FCGX_InitRequest(&request, 0, 0);  //初始化request

    char *querystring = FCGX_GetParam("QUERY_STRING", request.envp);     //得到获取数据的长度
    long  len = strtol(contentLength, NULL, 10);    //将contentLength转换为十进制long类型
    for (;;)
    {
        static pthread_mutex_t accept_mutex = PTHREAD_MUTEX_INITIALIZER;
        static pthread_mutex_t counts_mutex = PTHREAD_MUTEX_INITIALIZER;

        /* Some platforms require accept() serialization, some don't.. */
        pthread_mutex_lock(&accept_mutex);
        rc = FCGX_Accept_r(&request);
        pthread_mutex_unlock(&accept_mutex);

        if (rc < 0)
            break;

        server_name = FCGX_GetParam("SERVER_NAME", request.envp); //从环境变量中获取server_name 
      //输出
        FCGX_FPrintF(request.out,
            "Content-type: text/html\r\n"
            "\r\n"
            "<title>FastCGI Hello! (multi-threaded C, fcgiapp library)</title>"
            "<h1>FastCGI Hello! (multi-threaded C, fcgiapp library)</h1>"
            "Thread %d, Process %ld<p>"
            "Request counts for %d threads running on host <i>%s</i><p><code>",
            thread_id, pid, THREAD_COUNT, server_name ? server_name : "?");

        sleep(2);

        pthread_mutex_lock(&counts_mutex);
        ++counts[thread_id];
        for (i = 0; i < THREAD_COUNT; i++)
            FCGX_FPrintF(request.out, "%5d " , counts[i]);
        pthread_mutex_unlock(&counts_mutex);
      //释放掉request
        FCGX_Finish_r(&request);
    }

    return NULL;
}

int main(void)
{
    int i;
    pthread_t id[THREAD_COUNT];

    FCGX_Init();  //初始化
  
    for (i = 1; i < THREAD_COUNT; i++)
        pthread_create(&id[i], NULL, doit, (void*)i);

    doit(0);

    return 0;
}

/*
作者：温暖春阳
链接：https://www.jianshu.com/p/79f8975ea90d
來源：简书
*/
