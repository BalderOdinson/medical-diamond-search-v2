#!/bin/bash

if [ $# -gt 4 ] || [ $# -lt 2 ] || [ "$1" = "--help"  ] || [ "$1" = "-h" ]  ; then
    echo "Extracts frames from videos.\n\nArgs:\n 1. directory with videos\n 2. frame output directory 3. output directory for decoding 4. -c or --cache do not recreate existing frames";
    exit 0;
fi

if [ ! -d $1 ]; then
    echo "Input directory must be a valid directory!";
    exit 1;
fi

mkdir -p "$2"

for filename in $1/*.*; do
    outdir="$2/$(basename "$filename" | cut -d. -f1)"
    if [ "$4" = "--cache" ] || [ "$4" = "-c" ] ; then
      if [ -d $outdir ] ; then
          continue
      fi
    fi
    mkdir -p "$outdir"
    if [ -d $3 ]; then
        mkdir -p "$3/$(basename "$filename" | cut -d. -f1)/encoded"
        mkdir -p "$3/$(basename "$filename" | cut -d. -f1)/decoded"
    fi
    ffmpeg -i "$filename" "$outdir/%d.bmp" -hide_banner
done
