#include "HDDFomatMan.h"

#include <iostream>
#include <wx/msgdlg.h>
#include <wx/arrstr.h>
#include <wx/utils.h>


#include "PFSShell.h"

extern
PFSShell PFSSHELL;
//(*InternalHeaders(HDDFomatMan)




//(*IdInit(HDDFomatMan)




BEGIN_EVENT_TABLE(HDDFomatMan,wxDialog)
	//(*EventTable(HDDFomatMan)
	//*)
END_EVENT_TABLE()

HDDFomatMan::HDDFomatMan(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(HDDFomatMan)


























    wxListItem col1;
    col1.SetId(0);
    col1.SetText( _("ID") );
    col1.SetWidth(350);
    HDDList->InsertColumn(0, col1);
    wxListItem col2;
    col2.SetId(1);
    col2.SetText( _("Device") );
    col2.SetWidth(350);
    HDDList->InsertColumn(1, col2);
    wxListItem col3;
    col3.SetId(2);
    col3.SetText( _("Interface") );
    col3.SetWidth(350);
    HDDList->InsertColumn(2, col3);

    wxString line;
	bool OK = false;
	wxArrayString RET, ERR;

	long retcode = wxExecute("wmic diskdrive get Caption,DeviceID,InterfaceType", RET, ERR, wxEXEC_SYNC);
	if (retcode == 0)
    {
        for (size_t x=0; x<RET.GetCount();x++)
        {
            line = RET.Item(x);
            if (line == wxEmptyString || x == 0)
                continue;

            std::cout << line << '@'<< x << "\n";
            std::cout << line.SubString(line.find("\\\\.\\PHYSICALDRIVE"), line.find_first_of(' ', line.find("\\\\.\\PHYSICALDRIVE"))) << "\n";
            std::cout << line.Mid(line.find_first_of(' ', line.find("\\\\.\\PHYSICALDRIVE"))) << "|\n";
            std::cout << line.SubString(0, line.find("\\\\.\\PHYSICALDRIVE")-1) << "\n";
            long itemIndex = HDDList->InsertItem(0, line.SubString(line.find("\\\\.\\PHYSICALDRIVE"), line.find_first_of(' ', line.find("\\\\.\\PHYSICALDRIVE"))));// col. 1
            HDDList->SetItem(itemIndex, 1, line.SubString(0, line.find("\\\\.\\PHYSICALDRIVE")-1));
            HDDList->SetItem(itemIndex, 2, line.Mid(line.find_first_of(' ', line.find("\\\\.\\PHYSICALDRIVE"))));
        }
    }//*/
}

HDDFomatMan::~HDDFomatMan()
{
	//(*Destroy(HDDFomatMan)
	//*)
}


void HDDFomatMan::OnFormatClick(wxCommandEvent& event)
{
    wxString HDD ;
    long item = -1;
    if ( (item = HDDList->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND)
        HDD = HDDList->GetItemText(item, 0);
    else
        return;
    if (wxMessageBox(_("This Operation will wipe ALL THE DATA inside this hard drive\nContinue?"), wxMessageBoxCaptionStr, wxICON_WARNING|wxYES_NO|wxNO_DEFAULT)
        == wxNO) return;

    for (int x=0; x<3;x++)
    {
        if (wxMessageBox(wxString::Format(_("Do you really want to proceed?\nthis will wipe all data on device %s"), HDD), wxString::Format("%d/3", x), wxICON_WARNING|wxYES_NO|wxNO_DEFAULT)
            == wxNO) return;
    }

    std::cout << "WILL FORMAT NOW\n";
    PFSSHELL.SelectDevice(HDD.ToStdString());
    wxBeginBusyCursor();
    int ret = PFSSHELL.FormatDevice();
    wxEndBusyCursor();
    if (ret < 0)
        wxMessageBox(wxString::Format(_("HDD format failed\nError code is %d\nsee console log for more information"), ret), wxMessageBoxCaptionStr, wxICON_ERROR);
    else
        wxMessageBox(_("HDD was successfully formated.\nDefault partitions have been created!"), wxMessageBoxCaptionStr, wxICON_INFORMATION);

    PFSSHELL.CloseDevice();
}

void HDDFomatMan::OnHDDListItemSelect(wxListEvent& event)
{
    Format->Enable();
}

void HDDFomatMan::OnHDDListItemDeselect(wxListEvent& event)
{
    Format->Enable(false);
}