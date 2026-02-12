#include "config.h"

#include <stdio.h>
#include <string.h>

static void print_usage(void) {
    puts("pdfhenshu (portable prototype)");
    puts("Usage:");
    puts("  pdfhenshu --show-config");
    puts("  pdfhenshu rotate <input.pdf> <output.pdf> <page-range> <angle>");
    puts("  pdfhenshu extract <input.pdf> <output.pdf> <page-range>");
    puts("  pdfhenshu merge <output.pdf> <input1.pdf> <input2.pdf> [...]");
    puts("");
    puts("Note: current build prints planned backend command (qpdf integration step).\n");
}

static int cmd_rotate(int argc, char **argv, const PdfhenshuConfig *cfg) {
    if (argc != 6) {
        fputs("rotate: invalid args\n", stderr);
        return 2;
    }
    if (strcmp(argv[5], "90") && strcmp(argv[5], "180") && strcmp(argv[5], "270")) {
        fputs("rotate: angle must be 90/180/270 (arbitrary correction is intentionally unsupported)\n", stderr);
        return 2;
    }
    printf("[plan] %s --rotate=%s:%s -- %s %s\n",
           cfg->qpdf_path, argv[4], argv[5], argv[2], argv[3]);
    return 0;
}

static int cmd_extract(int argc, char **argv, const PdfhenshuConfig *cfg) {
    if (argc != 5) {
        fputs("extract: invalid args\n", stderr);
        return 2;
    }
    printf("[plan] %s %s --pages %s %s -- %s\n",
           cfg->qpdf_path, argv[2], argv[2], argv[4], argv[3]);
    return 0;
}

static int cmd_merge(int argc, char **argv, const PdfhenshuConfig *cfg) {
    int i;
    if (argc < 5) {
        fputs("merge: invalid args\n", stderr);
        return 2;
    }
    printf("[plan] %s --empty --pages", cfg->qpdf_path);
    for (i = 3; i < argc; ++i) {
        printf(" %s 1-z", argv[i]);
    }
    printf(" -- %s\n", argv[2]);
    return 0;
}

int main(int argc, char **argv) {
    PdfhenshuConfig cfg;

    config_init_default(&cfg);
    (void)config_load_portable(&cfg, ".");

    if (argc <= 1) {
        print_usage();
        return 0;
    }
    if (strcmp(argv[1], "--show-config") == 0) {
        config_print(&cfg);
        return 0;
    }
    if (strcmp(argv[1], "rotate") == 0) {
        return cmd_rotate(argc, argv, &cfg);
    }
    if (strcmp(argv[1], "extract") == 0) {
        return cmd_extract(argc, argv, &cfg);
    }
    if (strcmp(argv[1], "merge") == 0) {
        return cmd_merge(argc, argv, &cfg);
    }

    print_usage();
    return 1;
}
