#include "aboutmessage.h"

AboutMessage::AboutMessage()
{

    setText("<font size = '4'><a href=\"www.sonificationworkstation.org\" style=\"color:#8DB600\">Sonification Workstation website.</a><br>"
            "<br>"
            "Originally developed at <a href=\"www.mat.ucsb.edu\" style=\"color:#8DB600\">MAT</a>.<br>"
            "<br>"
            "Icons from <a href=\"www.flaticon.com\" style=\"color:#8DB600\">FlatIcon</a> authors:<br>"
            "<br>"
            "<a href=\"www.flaticon.com/authors/smashicons\" style=\"color:#8DB600\">Smashicons</a><br>"
            "<a href=\"www.flaticon.com/authors/situ-herrera\" style=\"color:#8DB600\">Situ Herrera</a><br>"
            "<a href=\"www.freepik.com\" style=\"color:#8DB600\">Freepik</a><br>"
            );

    setTextInteractionFlags(Qt::TextBrowserInteraction);
    setTextFormat(Qt::RichText);



}

