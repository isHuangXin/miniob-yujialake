python3 miniob_test.py \
        --db-base-dir=../../build/ \
        --test-case-dir=./test  \
        --test-case-scores=case-scores.json \
        --test-cases=primary-join-tables,2022-join-tables \
        --test-result-dir=result \
        --test-result-tmp-dir=./result_tmp \
        --use-unix-socket \
        --git-repo=https://github.com/isHuangXin/miniob-yujialake/tree/agg-func \
        --git-branch=agg-func \
        --code-type=none \
        --target-dir=./miniob \
        --log=stdout \
        --compile-make-args=-j12 \