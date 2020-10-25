if [ ! $# -eq 1 ] || [ "$1" = "--help"  ] || [ "$1" = "-h" ]  ; then
    echo "Create video from frames.\n\nArgs:\n 1. output directory with frames";
    exit 0;
fi

if [ ! -d $1 ]; then
    echo "Input directory must be a valid directory!";
    exit 1;
fi

ffmpeg -framerate 24 -i "$1/decoded/%d.bmp" -c:v libx264 -vf fps=24 -pix_fmt yuv420p "$1/decoded/video.mp4"