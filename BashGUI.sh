#!/bin/sh
: ${DIALOG:=dialog}
case "$DIALOG" in
*dialog*)
        OPTS="$OPTS --cr-wrap"
        high=10
        ;;
*whiptail*)
        high=12
        ;;
esac
rows=$(stty size | cut -d' ' -f1)
[ -z "$rows" ] && rows=$high
[ $rows -gt $high ] && rows=$high
cols=$(stty size | cut -d' ' -f2)
$DIALOG --backtitle "Package configuration" \
       --title "Configuring sun-java6-jre" \
       $OPTS \
       --yesno '\nIn order to install this package, you must accept the license terms, the "Operating System Distributor License for Java" (DLJ), v1.1. Not accepting will cancel the installation.\n\nDo you accept the DLJ license terms?' $rows $((cols - 5))