#ifndef PDFHENSHU_CONFIG_H
#define PDFHENSHU_CONFIG_H

#include <stddef.h>

#define PDFHENSHU_PATH_MAX 512

typedef struct {
    char runtime_dir[PDFHENSHU_PATH_MAX];
    char qpdf_path[PDFHENSHU_PATH_MAX];
    char renderer_path[PDFHENSHU_PATH_MAX];
    int thumbnail_dpi;
} PdfhenshuConfig;

void config_init_default(PdfhenshuConfig *cfg);
int config_load_portable(PdfhenshuConfig *cfg, const char *base_dir);
void config_print(const PdfhenshuConfig *cfg);

#endif
