#ifndef FATORA_MODULE_H
#define FATORA_MODULE_H

typedef struct decom_h *decom_t;
typedef struct mdc_mmc_h *mdc_mmc_t;

int decompor(unsigned int num, int *array, int n);

void destroy_decom_t(decom_t list);
void destroy_decom_t(decom_t list);

void create_mmc_mdc_t(mdc_mmc_t *list);
void destroy_mdc_mmc_t(mdc_mmc_t list);

decom_t contar_indices(int *array, int max);
decom_t ver_indice(decom_t list1, decom_t list2, unsigned int verifica);
mdc_mmc_t mdc_mmc_decomp(int num1, int num2);

void printar(decom_t list);
void printar_list1(mdc_mmc_t list);
void printar_list2(mdc_mmc_t list);
void printar_list_mmc(mdc_mmc_t list);
void printar_list_mdc(mdc_mmc_t list);

unsigned int get_mdc(mdc_mmc_t list);
unsigned int get_mmc(mdc_mmc_t list);

#endif