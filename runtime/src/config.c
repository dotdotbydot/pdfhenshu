#include "config.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void trim(char *s) {
    size_t len = strlen(s);
    while (len > 0 && isspace((unsigned char)s[len - 1])) {
        s[--len] = '\0';
    }
    size_t start = 0;
    while (s[start] && isspace((unsigned char)s[start])) {
        start++;
    }
    if (start > 0) {
        memmove(s, s + start, strlen(s + start) + 1);
    }
}

static void set_value(PdfhenshuConfig *cfg, const char *key, const char *val) {
    if (strcmp(key, "runtime_dir") == 0) {
        snprintf(cfg->runtime_dir, sizeof(cfg->runtime_dir), "%s", val);
    } else if (strcmp(key, "qpdf_path") == 0) {
        snprintf(cfg->qpdf_path, sizeof(cfg->qpdf_path), "%s", val);
    } else if (strcmp(key, "renderer_path") == 0) {
        snprintf(cfg->renderer_path, sizeof(cfg->renderer_path), "%s", val);
    } else if (strcmp(key, "thumbnail_dpi") == 0) {
        cfg->thumbnail_dpi = atoi(val);
        if (cfg->thumbnail_dpi <= 0) {
            cfg->thumbnail_dpi = 72;
        }
    }
}

void config_init_default(PdfhenshuConfig *cfg) {
    snprintf(cfg->runtime_dir, sizeof(cfg->runtime_dir), "runtime");
    snprintf(cfg->qpdf_path, sizeof(cfg->qpdf_path), "runtime/bin/qpdf");
    snprintf(cfg->renderer_path, sizeof(cfg->renderer_path), "runtime/bin/mutool");
    cfg->thumbnail_dpi = 96;
}

int config_load_portable(PdfhenshuConfig *cfg, const char *base_dir) {
    char path[PDFHENSHU_PATH_MAX];
    FILE *fp;
    char line[1024];

    snprintf(path, sizeof(path), "%s/runtime/pdfhenshu.ini", base_dir);
    fp = fopen(path, "r");
    if (!fp) {
        return -1;
    }

    while (fgets(line, sizeof(line), fp)) {
        char *eq;
        trim(line);
        if (line[0] == '\0' || line[0] == '#' || line[0] == ';') {
            continue;
        }
        eq = strchr(line, '=');
        if (!eq) {
            continue;
        }
        *eq = '\0';
        eq++;
        trim(line);
        trim(eq);
        set_value(cfg, line, eq);
    }

    fclose(fp);
    return 0;
}

void config_print(const PdfhenshuConfig *cfg) {
    printf("runtime_dir   : %s\n", cfg->runtime_dir);
    printf("qpdf_path     : %s\n", cfg->qpdf_path);
    printf("renderer_path : %s\n", cfg->renderer_path);
    printf("thumbnail_dpi : %d\n", cfg->thumbnail_dpi);
}
