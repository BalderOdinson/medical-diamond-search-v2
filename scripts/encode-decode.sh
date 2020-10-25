if [ ! $# -eq 1 ] || [ "$1" = "--help"  ] || [ "$1" = "-h" ]  ; then
    echo "Create video from frames.\n\nArgs:\n 1. output directory with frames";
    exit 0;
fi

if [ ! -d $1 ]; then
    echo "Input directory must be a valid directory!";
    exit 1;
fi

/home/oshikuru/Git/mds/cmake-build-release/mds-encoder/mds-encoder-cli "$(basename "$1")"
/home/oshikuru/Git/mds/cmake-build-release/mds-decoder/mds-decoder-cli "$(basename "$1")"
sh /home/oshikuru/Git/mds/scripts/make-video.sh "$1"