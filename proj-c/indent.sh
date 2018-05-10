#!/usr/bin/env sh

indent include/* src/*.c src/lib/*.c src/test/*.c \
    --blank-lines-after-procedures \
    --braces-on-func-def-line \
    --braces-on-if-line \
    --braces-on-struct-decl-line \
    --cuddle-do-while \
    --cuddle-else \
    --indent-level4 \
    --continue-at-parentheses \
    --no-space-after-casts \
    --no-space-after-function-call-names \
    --no-space-after-parentheses \
    --dont-break-procedure-type \
    --leave-optional-blank-lines \
    --line-length140 \
    --no-tabs \
    --space-after-for \
    --space-after-if \
    --space-after-while \
    --start-left-side-of-comments \
    --swallow-optional-blank-lines \
    --tab-size4 \
    -T USER \
    -T POST \
    -T TAG_COUNT \
    -T xmlHashTable

# Remove trailing whitespace
sed -i 's/[ \t]*$//' include/* src/*.c src/lib/*.c src/test/*.c
