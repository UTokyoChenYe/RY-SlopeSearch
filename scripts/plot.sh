#!/bin/bash

# Plot Fk curve
python ./plot_F_k.py \
    "/big/chenye/result/RY-SlopeSearch/2025-10-26_08-13-19/seq_NC_007946.1 Escherichia coli UTI89, complete sequence_vs_seq_NC_007606.1 Shigella dysenteriae Sd197, complete sequence_Fk.csv" \
    "/big/chenye/result/RY-SlopeSearch/2025-10-26_08-03-43/seq_NC_007946.1 Escherichia coli UTI89, complete sequence_vs_seq_NC_007606.1 Shigella dysenteriae Sd197, complete sequence_Fk.csv" \
    --log \
    --save /big/chenye/result/RY-SlopeSearch/2025-10-26_08-03-43/Fk.png

python ./plot_F_k.py \
    "/big/chenye/result/RY-SlopeSearch/2025-10-26_08-13-19/seq_NC_007946.1 Escherichia coli UTI89, complete sequence_vs_seq_NC_007606.1 Shigella dysenteriae Sd197, complete sequence_Fk.csv" \
    "/big/chenye/result/RY-SlopeSearch/2025-10-26_08-03-43/seq_NC_007946.1 Escherichia coli UTI89, complete sequence_vs_seq_NC_007606.1 Shigella dysenteriae Sd197, complete sequence_Fk.csv" \
    --save /big/chenye/result/RY-SlopeSearch/2025-10-26_08-03-43/Fk_no_log.png