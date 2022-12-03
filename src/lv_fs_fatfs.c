/**
 * @file lv_fs_fatfs.c
 *
 */
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_fs_fatfs.h"
#include "conf.h"
#include "ff.h"
#include <lvgl.h>
#include "rtos_externs.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void fs_init(void);

static void *fs_open(lv_fs_drv_t *drv, const char *path, lv_fs_mode_t mode);
static lv_fs_res_t fs_close(lv_fs_drv_t *drv, void *file_p);
static lv_fs_res_t fs_read(lv_fs_drv_t *drv, void *file_p, void *buf, uint32_t btr, uint32_t *br);
static lv_fs_res_t fs_write(lv_fs_drv_t *drv, void *file_p, const void *buf, uint32_t btw, uint32_t *bw);
static lv_fs_res_t fs_seek(lv_fs_drv_t *drv, void *file_p, uint32_t pos, lv_fs_whence_t whence);
// static lv_fs_res_t fs_size(lv_fs_drv_t * drv, void * file_p, uint32_t * size_p);
static lv_fs_res_t fs_tell(lv_fs_drv_t *drv, void *file_p, uint32_t *pos_p);

static void *fs_dir_open(lv_fs_drv_t *drv, const char *path);
static lv_fs_res_t fs_dir_read(lv_fs_drv_t *drv, void *rddir_p, char *fn);
static lv_fs_res_t fs_dir_close(lv_fs_drv_t *drv, void *rddir_p);

static void *spiffs_open(lv_fs_drv_t *drv, const char *path, lv_fs_mode_t mode);
static lv_fs_res_t spiffs_close(lv_fs_drv_t *drv, void *file_p);
static lv_fs_res_t spiffs_read(lv_fs_drv_t *drv, void *file_p, void *buf, uint32_t btr, uint32_t *br);
static lv_fs_res_t spiffs_write(lv_fs_drv_t *drv, void *file_p, const void *buf, uint32_t btw, uint32_t *bw);
static lv_fs_res_t spiffs_seek(lv_fs_drv_t *drv, void *file_p, uint32_t pos, lv_fs_whence_t whence);
static lv_fs_res_t spiffs_tell(lv_fs_drv_t *drv, void *file_p, uint32_t *pos_p);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
/* Create a type to store the required data about your file.*/
typedef FIL file_t;
typedef FILE *spiffs_file_t;

/*Similarly to `file_t` create a type for directory reading too */
typedef FF_DIR dir_t;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_fs_fatfs_init(void)
{
    /*----------------------------------------------------
     * Initialize your storage device and File System
     * -------------------------------------------------*/
    fs_init();

    /*---------------------------------------------------
     * Register the file system interface in LVGL
     *--------------------------------------------------*/

    /* Add a simple drive to open images */
    static lv_fs_drv_t fs_drv;
    lv_fs_drv_init(&fs_drv);

    /*Set up fields...*/
    fs_drv.letter = SD_DRIVE_LETTER;
    fs_drv.open_cb = fs_open;
    fs_drv.close_cb = fs_close;
    fs_drv.read_cb = fs_read;
    fs_drv.write_cb = fs_write;
    fs_drv.seek_cb = fs_seek;
    fs_drv.tell_cb = fs_tell;

    fs_drv.dir_close_cb = fs_dir_close;
    fs_drv.dir_open_cb = fs_dir_open;
    fs_drv.dir_read_cb = fs_dir_read;

    lv_fs_drv_register(&fs_drv);

    /* SPIFFS flash drive */
    static lv_fs_drv_t spiffs_drv;
    lv_fs_drv_init(&spiffs_drv);

    /*Set up fields...*/
    spiffs_drv.letter = FLASH_DRIVE_LETTER;
    spiffs_drv.open_cb = spiffs_open;
    spiffs_drv.close_cb = spiffs_close;
    spiffs_drv.read_cb = spiffs_read;
    spiffs_drv.write_cb = spiffs_write;
    spiffs_drv.seek_cb = spiffs_seek;
    spiffs_drv.tell_cb = spiffs_tell;

    lv_fs_drv_register(&spiffs_drv);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*Initialize your Storage device and File system.*/
static void fs_init(void)
{
    /* Initialize the SD card and FatFS itself.
     * Better to do it in your code to keep this library utouched for easy updating*/
}

/**
 * Open a file
 * @param drv       pointer to a driver where this function belongs
 * @param path      real path to the file (e.g. /folder/file.txt)
 * @param mode      read: FS_MODE_RD, write: FS_MODE_WR, both: FS_MODE_RD | FS_MODE_WR
 * @return          a file descriptor or NULL on error
 */
static void *fs_open(lv_fs_drv_t *drv, const char *path, lv_fs_mode_t mode)
{
    uint8_t flags = 0;

    if (mode == LV_FS_MODE_WR)
        flags = FA_WRITE | FA_OPEN_ALWAYS;
    else if (mode == LV_FS_MODE_RD)
        flags = FA_READ;
    else if (mode == (LV_FS_MODE_WR | LV_FS_MODE_RD))
        flags = FA_READ | FA_WRITE | FA_OPEN_ALWAYS;

    /* Get fatfs path including drive no. */
    char complete_path[strlen(path) + 2];
    complete_path[1] = ':';
    complete_path[2] = '\0';
    switch (drv->letter)
    {
    case 'S':
        complete_path[0] = '0';
        break;
    // case 'F':
    //     complete_path[0] = '1';
    //     break;
    default:
        return NULL;
    }
    strcat(complete_path, path);

    FIL *f = lv_mem_alloc(sizeof(FIL));
    if (f == NULL)
    {
        LV_LOG_ERROR("No memory to open file!");
        return NULL;
    }

    if (drv->letter == 'S') xSemaphoreTake(SDMutex, portMAX_DELAY);
    FRESULT res = f_open(f, path, flags);
    if (drv->letter == 'S') xSemaphoreGive(SDMutex);

    if (res == FR_OK)
    {
        if (drv->letter == 'S') xSemaphoreTake(SDMutex, portMAX_DELAY);
        f_lseek(f, 0);
        if (drv->letter == 'S') xSemaphoreGive(SDMutex);
        return f;
    }
    else
    {
        LV_LOG_ERROR("Unable to open file! Result was FRESULT::%d, Path:%s", res, path);
        lv_mem_free(f);
        return NULL;
    }
}

/**
 * Close an opened file
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable. (opened with fs_open)
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_close(lv_fs_drv_t *drv, void *file_p)
{
    if (drv->letter == 'S') xSemaphoreTake(SDMutex, portMAX_DELAY);
    f_close(file_p);
    if (drv->letter == 'S') xSemaphoreGive(SDMutex);

    lv_mem_free(file_p);
    return LV_FS_RES_OK;
}

/**
 * Read data from an opened file
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable.
 * @param buf       pointer to a memory block where to store the read data
 * @param btr       number of Bytes To Read
 * @param br        the real number of read bytes (Byte Read)
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_read(lv_fs_drv_t *drv, void *file_p, void *buf, uint32_t btr, uint32_t *br)
{
    if (drv->letter == 'S') xSemaphoreTake(SDMutex, portMAX_DELAY);
    FRESULT res = f_read(file_p, buf, btr, (UINT *)br);
    if (drv->letter == 'S') xSemaphoreGive(SDMutex);

    if (res == FR_OK)
        return LV_FS_RES_OK;
    else
        return LV_FS_RES_UNKNOWN;
}

/**
 * Write into a file
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable
 * @param buf       pointer to a buffer with the bytes to write
 * @param btw       Bytes To Write
 * @param bw        the number of real written bytes (Bytes Written). NULL if unused.
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_write(lv_fs_drv_t *drv, void *file_p, const void *buf, uint32_t btw, uint32_t *bw)
{
    if (drv->letter == 'S') xSemaphoreTake(SDMutex, portMAX_DELAY);
    FRESULT res = f_write(file_p, buf, btw, (UINT *)bw);
    if (drv->letter == 'S') xSemaphoreGive(SDMutex);

    if (res == FR_OK)
        return LV_FS_RES_OK;
    else
        return LV_FS_RES_UNKNOWN;
}

/**
 * Set the read write pointer. Also expand the file size if necessary.
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable. (opened with fs_open )
 * @param pos       the new position of read write pointer
 * @param whence    tells from where to interpret the `pos`. See @lv_fs_whence_t
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_seek(lv_fs_drv_t *drv, void *file_p, uint32_t pos, lv_fs_whence_t whence)
{
    if (drv->letter == 'S') xSemaphoreTake(SDMutex, portMAX_DELAY);
    switch (whence)
    {
    case LV_FS_SEEK_SET:
        f_lseek(file_p, pos);
        break;
    case LV_FS_SEEK_CUR:
        f_lseek(file_p, f_tell((FIL *)file_p) + pos);
        break;
    case LV_FS_SEEK_END:
        f_lseek(file_p, f_size((FIL *)file_p) + pos);
        break;
    default:
        break;
    }
    if (drv->letter == 'S') xSemaphoreGive(SDMutex);

    return LV_FS_RES_OK;
}

/**
 * Give the position of the read write pointer
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable.
 * @param pos_p     pointer to to store the result
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_tell(lv_fs_drv_t *drv, void *file_p, uint32_t *pos_p)
{
    if (drv->letter == 'S') xSemaphoreTake(SDMutex, portMAX_DELAY);
    *pos_p = f_tell(((FIL *)file_p));
    if (drv->letter == 'S') xSemaphoreGive(SDMutex);

    return LV_FS_RES_OK;
}

/**
 * Initialize a 'lv_fs_dir_t' variable for directory reading
 * @param drv       pointer to a driver where this function belongs
 * @param path      path to a directory
 * @return          pointer to the directory read descriptor or NULL on error
 */
static void *fs_dir_open(lv_fs_drv_t *drv, const char *path)
{
    FF_DIR *d = lv_mem_alloc(sizeof(FF_DIR));
    if (d == NULL)
        return NULL;

    /* Get fatfs path including drive no. */
    char complete_path[strlen(path) + 2];
    complete_path[1] = ':';
    complete_path[2] = '\0';
    switch (drv->letter)
    {
    case 'S':
        complete_path[0] = '0';
        break;
    // case 'F':
    //     complete_path[0] = '1';
    //     break;
    default:
        return NULL;
    }
    strcat(complete_path, path);

    if (drv->letter == 'S') xSemaphoreTake(SDMutex, portMAX_DELAY);
    FRESULT res = f_opendir(d, path);
    if (drv->letter == 'S') xSemaphoreGive(SDMutex);
    if (res != FR_OK)
    {
        lv_mem_free(d);
        d = NULL;
    }
    return d;
}

/**
 * Read the next filename form a directory.
 * The name of the directories will begin with '/'
 * @param drv       pointer to a driver where this function belongs
 * @param rddir_p   pointer to an initialized 'lv_fs_dir_t' variable
 * @param fn        pointer to a buffer to store the filename
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_dir_read(lv_fs_drv_t *drv, void *dir_p, char *fn)
{
    FRESULT res;
    FILINFO fno;
    fn[0] = '\0';

    if (drv->letter == 'S') xSemaphoreTake(SDMutex, portMAX_DELAY);
    do
    {
        res = f_readdir(dir_p, &fno);
        if (res != FR_OK)
            return LV_FS_RES_UNKNOWN;

        if (fno.fattrib & AM_DIR)
        {
            fn[0] = '/';
            strcpy(&fn[1], fno.fname);
        }
        else
            strcpy(fn, fno.fname);

    } while (strcmp(fn, "/.") == 0 || strcmp(fn, "/..") == 0);
    if (drv->letter == 'S') xSemaphoreGive(SDMutex);

    return LV_FS_RES_OK;
}

/**
 * Close the directory reading
 * @param drv       pointer to a driver where this function belongs
 * @param rddir_p   pointer to an initialized 'lv_fs_dir_t' variable
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t fs_dir_close(lv_fs_drv_t *drv, void *dir_p)
{
    if (drv->letter == 'S') xSemaphoreTake(SDMutex, portMAX_DELAY);
    f_closedir(dir_p);
    if (drv->letter == 'S') xSemaphoreGive(SDMutex);

    lv_mem_free(dir_p);
    return LV_FS_RES_OK;
}

static void *spiffs_open(struct _lv_fs_drv_t *drv, const char *path, lv_fs_mode_t mode)
{
    (void)drv; /*Unused*/

    const char *flags = "";

    if (mode == LV_FS_MODE_WR)
        flags = "w";
    else if (mode == LV_FS_MODE_RD)
        flags = "r";
    else if (mode == (LV_FS_MODE_WR | LV_FS_MODE_RD))
        flags = "rb+";

    /*Make the path relative to the current directory (the projects root folder)*/

    char complete_path[strlen(path) + 7];
    sprintf(complete_path, "/spiffs%s", path);

    spiffs_file_t f = fopen(complete_path, flags);
    if (f == NULL)
        return NULL;

    /*Be sure we are the beginning of the file*/
    fseek(f, 0, SEEK_SET);

    return f;
}

static lv_fs_res_t spiffs_read(struct _lv_fs_drv_t *drv, void *file_p, void *buf, uint32_t btr, uint32_t *br)
{
    spiffs_file_t fp = file_p; /*Just avoid the confusing casings*/
    *br = fread(buf, 1, btr, fp);
    return LV_FS_RES_OK;
}

static lv_fs_res_t spiffs_write(lv_fs_drv_t *drv, void *file_p, const void *buf, uint32_t btw, uint32_t *bw)
{
    spiffs_file_t fp = file_p; /*Just avoid the confusing casings*/
    *bw = fwrite(buf, 1, btw, fp);
    return LV_FS_RES_OK;
}

static lv_fs_res_t spiffs_close(struct _lv_fs_drv_t *drv, void *file_p)
{
    spiffs_file_t fp = file_p; /*Just avoid the confusing casings*/
    fclose(fp);
    return LV_FS_RES_OK;
}

static lv_fs_res_t spiffs_seek(lv_fs_drv_t *drv, void *file_p, uint32_t pos, lv_fs_whence_t whence)
{
    spiffs_file_t fp = file_p; /*Just avoid the confusing casings*/
    fseek(fp, pos, whence);
    return LV_FS_RES_OK;
}

static lv_fs_res_t spiffs_tell(struct _lv_fs_drv_t *drv, void *file_p, uint32_t *pos_p)
{
    spiffs_file_t fp = file_p; /*Just avoid the confusing casings*/
    *pos_p = ftell(fp);
    return LV_FS_RES_OK;
}

#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
