/*
 *  Copyright (c) 2015 Intel Corporation. All rights reserved.
 *  This software is available to you under the BSD license below:
 *
 * *	Redistribution and use in source and binary forms, with or
 *	without modification, are permitted provided that the following
 *	conditions are met:
 *
 *	- Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**
**  Notice: micro benchmark ~ two nodes only
**
**  Features of Test:
**  1) small get latency test
**  2) getmem latency test to calculate latency of various sizes
**
*/

#include <latency_common.h>
#include <round_t_latency.h>
#include <stream_int_latency.h>

int main(int argc, char *argv[])
{

    latency_main(argc, argv);

    return 0;
}  /* end of main() */


void
long_element_round_trip_latency(perf_metrics_t data)
{
    long_element_round_trip_latency_get(data);
}

void
streaming_int_latency(perf_metrics_t data)
{
    streaming_int_g_latency(data);
}

void
streaming_latency(int len, perf_metrics_t *data)
{
    double start, end;
    int i = 0;

    if (data->my_node == 0) {

        for (i = 0; i < data->trials + data->warmup; i++) {
            if(i == data->warmup)
                start = perf_shmemx_wtime();

            shmem_getmem(data->dest, data->src, len, 1);
        }
        end = perf_shmemx_wtime();

        calc_and_print_results(start, end, len, *data);
    }
} /* latency/bw for one-way trip */
