#include "TFCard.h"

/*----------------------------------------------------------------------------------------
˵����
1.  Ϊ�˼���flash�洢�ռ������ʱ�䣬�ļ�ϵͳ����Ϊֻ֧��ascii��ֻ֧��ascii
    ��ζ���ļ���ֻ���Ƕ��ļ������ļ������ļ�����������8���ֽڣ�������ļ���
    �в��ܺ�����ֵķ��ţ������ļ������ܴ򿪻����ļ��������ض�
2.  SD������ʹ��SPI+DMA��������SPI_TX SPI_RX��USART3_TX UART4_TX��DMAx_Streamy
    ��ͻ����ʹ�ñ�SD����д����ʹ��USART3_TX UART4_TX����ʹ��DMA
3.  ʹ��f_sync���ڱ������ݣ��������ݶ�ʧ��������ͬ���ļ��ܺ�ʱ�����ÿ���ɴ�
    ��¼�󱣴�һ��
4.  ���ƺ����ݴ�������������໥�����������δ洢�����������򽵵ʹ���֡�ʣ�
    ����֡�ʸ��򽵵͵��δ洢��������
----------------------------------------------------------------------------------------*/

FRESULT Mount_Result;
FRESULT File_Result;

FATFS my_fats;
DIR my_dir;
FIL my_file;
FILINFO my_file_info;

char* filedir = "RM_DATA";
char filename[255] = "0.txt";

/*----------------------------------------------------------------------------------------
�������ܣ��Զ���ȡ�ļ���
----------------------------------------------------------------------------------------*/
static void AutoGetFileName(void)
{
    int file_num = 0;

    if(f_opendir(&my_dir, filedir)!=FR_OK)
    {
        f_mkdir(filedir);
        f_opendir(&my_dir, filedir);
    }

    do
    {
        f_readdir(&my_dir, &my_file_info);
        file_num++; //�����ļ���Ŀ���ļ����Լ�����ʽ����
    } while(my_file_info.fname[0]);

    sprintf(filename,"%s/%d.txt", filedir, file_num);
}

/*----------------------------------------------------------------------------------------
�������ܣ�SD������
----------------------------------------------------------------------------------------*/
void SD_Mount(void)
{
    SD_LowLevel_Init(); //��ʼ��SD����SPI DMA
    SD_Init();          //��ʼ��SDͨѶ

    Mount_Result = f_mount(&my_fats, "", 1);    //ʹ��FATFS��ʱ�򣬱�����ͨ��f_mount������ע��һ�������������ܿ�ʼ����API��ʹ��

    if(Mount_Result!=FR_OK)
    {
        printf("SD Card mount failed\r\n");     //����ʧ��
    }
    else
    {
        printf("SD Card mount succeed\r\n");    //���سɹ�
        SD_GetCardInfo(&SD_CardInfo);           //��ȡSD��Ϣ
        ShowCardInfo(&SD_CardInfo);             //��ӡSD��Ϣ
        AutoGetFileName();                      //�Զ���ȡ�ļ���
        File_Result = f_open( &my_file, filename, FA_OPEN_ALWAYS|FA_READ|FA_WRITE );    //���ļ�
    }
}

/*----------------------------------------------------------------------------------------
�������ܣ�SD�����ݼ�¼
ע��ff.c�Դ���f_printf����һ��ȱ�ݣ����ܴ�ӡ����������������Լ�ʵ��
----------------------------------------------------------------------------------------*/
char SD_Data_Buf[255] = {0};
u8 SD_Data_Len = 0;
void SD_printf(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    SD_Data_Len = (u8)vsprintf(SD_Data_Buf, fmt, ap);	    //����ʽ�����ݴ�sz�ַ����ϣ����ظ�ʽ������

    static u32 cnt = 0;

    if(File_Result == FR_OK)
    {
        f_lseek(&my_file, my_file.fsize);   //f_lseek���ļ�ĩβ���൱����ĩ׷������
        f_puts(SD_Data_Buf, &my_file);

        cnt++;
        if(cnt==1000)           //���ڱ��棬�������ݶ�ʧ����ͬ���ļ��ܺ�ʱ�����ÿ���ɴμ�¼����һ��
        {
            f_sync(&my_file);   //����f_close����f_close���������ִ�к�����������ǰ�ļ��Ƿ���Ҫ����f_open
//            f_close(&my_file);
            cnt = 0;
        }
    }
    else
    {
        printf("can't open\r\n");
    }
}
