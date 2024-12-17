#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define MAX_RECORDS 1000
#define MAX_SITES 10

typedef struct {
    int site_id_num;
    int day_of_month;
    double wind_speed;
    double temperature;
} measured_data_t;

void find_unique_sites(measured_data_t data[], int count, int site_ids[], int *site_count) {
    *site_count = 0;
    for (int i = 0; i < count; i++) {
        int site_id = data[i].site_id_num;
        int found = 0;
        for (int j = 0; j < *site_count; j++) {
            if (site_ids[j] == site_id) {
                found = 1;
                break;
            }
        }
        if (!found) {
            site_ids[*site_count] = site_id;
            (*site_count)++;
        }
    }
}

int find_site_index(int site_ids[], int site_count, int site_id) {
    for (int i = 0; i < site_count; i++) {
        if (site_ids[i] == site_id) {
            return i;
        }
    }
    return -1;
}

void find_greatest_temperature_variation(measured_data_t data[], int count, int site_ids[], int site_count, int *site_id, double *variation) {
    double min_temp[MAX_SITES];
    double max_temp[MAX_SITES];
    
    for (int i = 0; i < MAX_SITES; i++) {
        min_temp[i] = DBL_MAX;
        max_temp[i] = DBL_MIN;
    }

    for (int i = 0; i < count; i++) {
        int index = find_site_index(site_ids, site_count, data[i].site_id_num);
        if (data[i].temperature < min_temp[index]) {
            min_temp[index] = data[i].temperature;
        }
        if (data[i].temperature > max_temp[index]) {
            max_temp[index] = data[i].temperature;
        }
    }

    *variation = 0.0;
    for (int i = 0; i < site_count; i++) {
        double temp_variation = max_temp[i] - min_temp[i];
        if (temp_variation > *variation) {
            *variation = temp_variation;
            *site_id = site_ids[i];
        }
    }
}

void find_highest_average_wind_speed(measured_data_t data[], int count, int site_ids[], int site_count, int *site_id, double *avg_speed) {
    double wind_speed_sum[MAX_SITES] = { 0 };
    int wind_speed_count[MAX_SITES] = { 0 };

    for (int i = 0; i < count; i++) {
        int index = find_site_index(site_ids, site_count, data[i].site_id_num);
        wind_speed_sum[index] += data[i].wind_speed;
        wind_speed_count[index]++;
    }

    *avg_speed = 0.0;
    for (int i = 0; i < site_count; i++) {
        if (wind_speed_count[i] > 0) {
            double avg = wind_speed_sum[i] / wind_speed_count[i];
            if (avg > *avg_speed) {
                *avg_speed = avg;
                *site_id = site_ids[i];
            }
        }
    }
}

int main() {
    measured_data_t data[MAX_RECORDS];
    int count = 0;

    FILE *file = fopen("Ch11No1_data.txt", "r");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    while (fscanf(file, "%d %d %lf %lf",
                  &data[count].site_id_num,
                  &data[count].day_of_month,
                  &data[count].wind_speed,
                  &data[count].temperature) == 4) {
        count++;
        if (count >= MAX_RECORDS) break;
    }
    fclose(file);

    int site_ids[MAX_SITES];
    int site_count;
    find_unique_sites(data, count, site_ids, &site_count);

    int temp_variation_site;
    double temp_variation;
    find_greatest_temperature_variation(data, count, site_ids, site_count, &temp_variation_site, &temp_variation);

    int avg_wind_site;
    double avg_wind_speed;
    find_highest_average_wind_speed(data, count, site_ids, site_count, &avg_wind_site, &avg_wind_speed);

    printf("Site with greatest temperature variation: %d (Variation: %.2lf degrees)\n", temp_variation_site, temp_variation);
    printf("Site with highest average wind speed: %d (Average speed: %.2lf knots)\n", avg_wind_site, avg_wind_speed);

    return 0;
}
