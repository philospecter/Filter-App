#pragma once
#include <string>
#include <msclr/marshal_cppstd.h>
#include "Image_Class.h"
#include "Filters.h"

namespace GUI {
    using namespace System;
    using namespace System::Drawing;
    using namespace System::Windows::Forms;
    using namespace System::IO;

    public ref class MyForm : public Form {
    public:
        MyForm() { InitializeUI(); originalBitmap=nullptr; resultBitmap=nullptr; }
    protected:
        ~MyForm() { if(originalBitmap) delete originalBitmap; if(resultBitmap) delete resultBitmap; }

    private:
        Bitmap^ originalBitmap;
        Bitmap^ resultBitmap;
        PictureBox^ originalBox;
        PictureBox^ resultBox;
        Label^ statusLabel;
        TextBox^ filterNumber;
        Button^ loadButton;
        Button^ applyButton;
        Button^ saveButton;
        Label^ filterDescription;

        void InitializeUI() {
            this->Text = L"PIXELFORGE | Image Studio";
            this->StartPosition = FormStartPosition::CenterScreen;
            this->ClientSize = Drawing::Size(1180, 760);
            this->MinimumSize = Drawing::Size(1000, 680);
            this->BackColor = Color::FromArgb(16, 20, 29);
            this->Font = gcnew Drawing::Font(L"Segoe UI", 10, FontStyle::Regular);

            Label^ brand = gcnew Label(); brand->Text=L"PIXELFORGE"; brand->ForeColor=Color::FromArgb(79,220,208); brand->Font=gcnew Drawing::Font(L"Segoe UI",22,FontStyle::Bold); brand->Location=Point(28,18); brand->AutoSize=true; Controls->Add(brand);
            Label^ subtitle=gcnew Label(); subtitle->Text=L"IMAGE PROCESSING STUDIO  /  C++ EDITION"; subtitle->ForeColor=Color::FromArgb(163,174,190); subtitle->Font=gcnew Drawing::Font(L"Segoe UI",9,FontStyle::Regular); subtitle->Location=Point(31,59); subtitle->AutoSize=true; Controls->Add(subtitle);
            Panel^ divider=gcnew Panel(); divider->BackColor=Color::FromArgb(48,60,74); divider->Location=Point(28,91); divider->Size=Drawing::Size(1124,1); Controls->Add(divider);

            Panel^ controlPanel=gcnew Panel(); controlPanel->BackColor=Color::FromArgb(25,31,43); controlPanel->Location=Point(28,116); controlPanel->Size=Drawing::Size(220,590); controlPanel->Anchor=AnchorStyles::Top|AnchorStyles::Bottom|AnchorStyles::Left; Controls->Add(controlPanel);
            Label^ tools=gcnew Label(); tools->Text=L"WORKSPACE"; tools->ForeColor=Color::White; tools->Font=gcnew Drawing::Font(L"Segoe UI",11,FontStyle::Bold); tools->Location=Point(18,18); tools->AutoSize=true; controlPanel->Controls->Add(tools);
            loadButton=MakeButton(L"Load image",Point(16,60),Drawing::Size(188,44),Color::FromArgb(42,57,74)); loadButton->Click+=gcnew EventHandler(this,&MyForm::LoadImage); controlPanel->Controls->Add(loadButton);
            Label^ numberLabel=gcnew Label(); numberLabel->Text=L"FILTER NUMBER"; numberLabel->ForeColor=Color::FromArgb(173,185,201); numberLabel->Location=Point(18,132); numberLabel->AutoSize=true; numberLabel->Font=gcnew Drawing::Font(L"Segoe UI",9,FontStyle::Bold); controlPanel->Controls->Add(numberLabel);
            filterNumber=gcnew TextBox(); filterNumber->Location=Point(16,160); filterNumber->Size=Drawing::Size(188,36); filterNumber->Font=gcnew Drawing::Font(L"Segoe UI",14,FontStyle::Bold); filterNumber->BackColor=Color::FromArgb(14,19,27); filterNumber->ForeColor=Color::White; filterNumber->BorderStyle=BorderStyle::FixedSingle; filterNumber->Text=L"1"; controlPanel->Controls->Add(filterNumber);
            filterDescription=gcnew Label(); filterDescription->Text=L"Enter a number from 1 to 18.\n\n1  Grayscale\n2  Black & White\n3  Invert\n4  Frame\n5  Flip\n6  Rotate\n7  Darken / Lighten\n8  Resize\n9  Merge\n10 Edge Detection\n11 Crop\n12 Blur\n13 Sunlight\n14 Old TV\n15 Purple\n16 Infrared\n17 Skew\n18 Oil Painting"; filterDescription->ForeColor=Color::FromArgb(188,199,214); filterDescription->Location=Point(18,215); filterDescription->Size=Drawing::Size(188,300); filterDescription->Font=gcnew Drawing::Font(L"Segoe UI",9); controlPanel->Controls->Add(filterDescription);
            applyButton=MakeButton(L"Apply operation",Point(16,522),Drawing::Size(188,44),Color::FromArgb(27,151,145)); applyButton->Click+=gcnew EventHandler(this,&MyForm::ApplyFilter); controlPanel->Controls->Add(applyButton);
            saveButton=MakeButton(L"Save result",Point(16,574),Drawing::Size(188,44),Color::FromArgb(42,57,74)); saveButton->Click+=gcnew EventHandler(this,&MyForm::SaveResult); controlPanel->Controls->Add(saveButton);

            Label^ originalTitle=gcnew Label(); originalTitle->Text=L"01  /  ORIGINAL"; originalTitle->ForeColor=Color::FromArgb(222,232,244); originalTitle->Font=gcnew Drawing::Font(L"Segoe UI",11,FontStyle::Bold); originalTitle->Location=Point(274,116); originalTitle->AutoSize=true; Controls->Add(originalTitle);
            Label^ resultTitle=gcnew Label(); resultTitle->Text=L"02  /  PROCESSED"; resultTitle->ForeColor=Color::FromArgb(79,220,208); resultTitle->Font=gcnew Drawing::Font(L"Segoe UI",11,FontStyle::Bold); resultTitle->Location=Point(714,116); resultTitle->AutoSize=true; Controls->Add(resultTitle);
            originalBox=MakePictureBox(Point(274,151),Drawing::Size(420,490)); Controls->Add(originalBox);
            resultBox=MakePictureBox(Point(714,151),Drawing::Size(438,490)); Controls->Add(resultBox);
            statusLabel=gcnew Label(); statusLabel->Text=L"Ready. Load an image to begin."; statusLabel->ForeColor=Color::FromArgb(154,170,190); statusLabel->Location=Point(274,664); statusLabel->Size=Drawing::Size(878,32); statusLabel->AutoEllipsis=true; Controls->Add(statusLabel);
            Label^ footer=gcnew Label(); footer->Text=L"C++ IMAGE PROCESSING  •  18 OPERATIONS"; footer->ForeColor=Color::FromArgb(92,108,128); footer->Font=gcnew Drawing::Font(L"Segoe UI",8,FontStyle::Bold); footer->Location=Point(30,722); footer->AutoSize=true; Controls->Add(footer);
        }
        Button^ MakeButton(String^ text,Point location,Drawing::Size size,Color color) { Button^ b=gcnew Button(); b->Text=text; b->Location=location; b->Size=size; b->FlatStyle=FlatStyle::Flat; b->FlatAppearance->BorderSize=0; b->BackColor=color; b->ForeColor=Color::White; b->Font=gcnew Drawing::Font(L"Segoe UI",10,FontStyle::Bold); b->Cursor=Windows::Forms::Cursors::Hand; return b; }
        PictureBox^ MakePictureBox(Point location,Drawing::Size size) { PictureBox^ p=gcnew PictureBox(); p->Location=location; p->Size=size; p->BackColor=Color::FromArgb(10,14,21); p->BorderStyle=BorderStyle::FixedSingle; p->SizeMode=PictureBoxSizeMode::Zoom; return p; }
        int AskInt(String^ title,String^ prompt,int defaultValue) {
            Form^ f=gcnew Form(); f->Text=title; f->ClientSize=Drawing::Size(360,145); f->StartPosition=FormStartPosition::CenterParent; f->BackColor=Color::FromArgb(25,31,43); f->ForeColor=Color::White; f->FormBorderStyle=FormBorderStyle::FixedDialog; f->MinimizeBox=false; f->MaximizeBox=false;
            Label^ l=gcnew Label(); l->Text=prompt; l->Location=Point(15,15); l->Size=Drawing::Size(330,38); f->Controls->Add(l);
            TextBox^ t=gcnew TextBox(); t->Text=defaultValue.ToString(); t->Location=Point(16,58); t->Width=328; f->Controls->Add(t);
            Button^ ok=gcnew Button(); ok->Text=L"Continue"; ok->DialogResult=System::Windows::Forms::DialogResult::OK; ok->Location=Point(236,98); f->Controls->Add(ok); f->AcceptButton=ok;
            if(f->ShowDialog(this)!=System::Windows::Forms::DialogResult::OK) { delete f; throw gcnew OperationCanceledException(); }
            int value; if(!Int32::TryParse(t->Text,value)) { delete f; throw gcnew ArgumentException("Please enter a valid whole number."); } delete f; return value;
        }
        double AskDouble(String^ title,String^ prompt,double defaultValue) {
            Form^ f=gcnew Form(); f->Text=title; f->ClientSize=Drawing::Size(360,145); f->StartPosition=FormStartPosition::CenterParent; f->BackColor=Color::FromArgb(25,31,43); f->ForeColor=Color::White; f->FormBorderStyle=FormBorderStyle::FixedDialog; f->MinimizeBox=false; f->MaximizeBox=false;
            Label^ l=gcnew Label(); l->Text=prompt; l->Location=Point(15,15); l->Size=Drawing::Size(330,38); f->Controls->Add(l);
            TextBox^ t=gcnew TextBox(); t->Text=defaultValue.ToString(); t->Location=Point(16,58); t->Width=328; f->Controls->Add(t);
            Button^ ok=gcnew Button(); ok->Text=L"Continue"; ok->DialogResult=System::Windows::Forms::DialogResult::OK; ok->Location=Point(236,98); f->Controls->Add(ok); f->AcceptButton=ok;
            if(f->ShowDialog(this)!=System::Windows::Forms::DialogResult::OK) { delete f; throw gcnew OperationCanceledException(); }
            double value; if(!Double::TryParse(t->Text,value)) { delete f; throw gcnew ArgumentException("Please enter a valid number."); } delete f; return value;
        }
        void LoadImage(Object^ sender,EventArgs^ e) {
            OpenFileDialog^ d=gcnew OpenFileDialog(); d->Filter=L"Image files|*.png;*.jpg;*.jpeg;*.bmp;*.gif;*.tif;*.tiff";
            if(d->ShowDialog()==System::Windows::Forms::DialogResult::OK) try {
                Bitmap^ temp=gcnew Bitmap(d->FileName); Bitmap^ copy=gcnew Bitmap(temp); delete temp;
                if(originalBitmap) delete originalBitmap; if(resultBitmap) delete resultBitmap; originalBitmap=copy; resultBitmap=nullptr; originalBox->Image=originalBitmap; resultBox->Image=nullptr; statusLabel->Text=L"Loaded: "+Path::GetFileName(d->FileName)+L". Enter an operation number.";
            } catch(Exception^ ex) { MessageBox::Show(ex->Message,L"Could not load image",MessageBoxButtons::OK,MessageBoxIcon::Error); }
            delete d;
        }
        void ApplyFilter(Object^ sender,EventArgs^ e) {
            if(originalBitmap==nullptr) { MessageBox::Show(L"Load an image first."); return; }
            int n; if(!Int32::TryParse(filterNumber->Text,n)||n<1||n>18) { MessageBox::Show(L"Enter an operation number from 1 to 18."); return; }
            String^ tempIn=Path::Combine(Path::GetTempPath(),Guid::NewGuid().ToString()+L".png"); String^ tempOut=Path::Combine(Path::GetTempPath(),Guid::NewGuid().ToString()+L".png");
            try {
                originalBitmap->Save(tempIn,Imaging::ImageFormat::Png);
                std::string nativeIn=msclr::interop::marshal_as<std::string>(tempIn); std::string nativeOut=msclr::interop::marshal_as<std::string>(tempOut);
                ::Image nativeImage(nativeIn); int a=0,b=0,c=0,d=0; double val=0; std::string extra="";
                switch(n) {
                case 4: a=AskInt(L"Frame",L"Frame style: 1 = simple, 2 = decorative",1); if(a<1||a>2) throw gcnew ArgumentException("Choose 1 or 2."); break;
                case 5: a=AskInt(L"Flip",L"Direction: 1 = horizontal, 2 = vertical",1); if(a<1||a>2) throw gcnew ArgumentException("Choose 1 or 2."); break;
                case 6: a=AskInt(L"Rotate",L"Angle: enter 90, 180, or 270",90); if(a!=90&&a!=180&&a!=270) throw gcnew ArgumentException("Choose 90, 180, or 270."); break;
                case 7: a=AskInt(L"Darken / Lighten",L"Percentage from -100 (darken) to 100 (lighten)",20); if(a < -100||a>100) throw gcnew ArgumentException("Enter a percentage from -100 to 100."); break;
                case 8: a=AskInt(L"Resize",L"New width in pixels",originalBitmap->Width); b=AskInt(L"Resize",L"New height in pixels",originalBitmap->Height); break;
                case 9: { OpenFileDialog^ d=gcnew OpenFileDialog(); d->Filter=L"Image files|*.png;*.jpg;*.jpeg;*.bmp;*.gif;*.tif;*.tiff"; d->Title=L"Choose second image to merge"; if(d->ShowDialog()!=System::Windows::Forms::DialogResult::OK){delete d;throw gcnew OperationCanceledException();} extra=msclr::interop::marshal_as<std::string>(d->FileName); delete d; break; }
                case 11: a=AskInt(L"Crop",L"Starting X coordinate",0); b=AskInt(L"Crop",L"Starting Y coordinate",0); c=AskInt(L"Crop",L"Crop width",originalBitmap->Width/2); d=AskInt(L"Crop",L"Crop height",originalBitmap->Height/2); break;
                case 12: a=AskInt(L"Blur",L"Strength from 1 to 5",2); break;
                case 17: val=AskDouble(L"Skew",L"Angle in degrees (5 to 30)",10); break;
                }
                ImageFilters::apply(nativeImage,n,a,b,c,d,val,extra); nativeImage.saveImage(nativeOut);
                Bitmap^ tempResult=gcnew Bitmap(tempOut); Bitmap^ resultCopy=gcnew Bitmap(tempResult); delete tempResult;
                if(resultBitmap) delete resultBitmap; resultBitmap=resultCopy; resultBox->Image=resultBitmap; statusLabel->Text=L"Operation "+n.ToString()+L" applied successfully.";
            } catch(OperationCanceledException^) { statusLabel->Text=L"Operation cancelled."; }
              catch(Exception^ ex) { MessageBox::Show(ex->Message,L"Could not apply operation",MessageBoxButtons::OK,MessageBoxIcon::Error); }
              catch(const std::exception& ex) { MessageBox::Show(gcnew String(ex.what()),L"Image processing error",MessageBoxButtons::OK,MessageBoxIcon::Error); }
            try { if(File::Exists(tempIn)) File::Delete(tempIn); if(File::Exists(tempOut)) File::Delete(tempOut); } catch(...) {}
        }
        void SaveResult(Object^ sender,EventArgs^ e) {
            if(resultBitmap==nullptr) { MessageBox::Show(L"Apply an operation before saving the result."); return; }
            SaveFileDialog^ d=gcnew SaveFileDialog(); d->Filter=L"PNG image|*.png|JPEG image|*.jpg|Bitmap image|*.bmp"; d->FileName=L"processed_image.png";
            if(d->ShowDialog()==System::Windows::Forms::DialogResult::OK) try { Imaging::ImageFormat^ fmt=Imaging::ImageFormat::Png; String^ ext=Path::GetExtension(d->FileName)->ToLower(); if(ext==L".jpg"||ext==L".jpeg")fmt=Imaging::ImageFormat::Jpeg; else if(ext==L".bmp")fmt=Imaging::ImageFormat::Bmp; resultBitmap->Save(d->FileName,fmt); statusLabel->Text=L"Saved: "+d->FileName; } catch(Exception^ ex) { MessageBox::Show(ex->Message,L"Save failed"); }
            delete d;
        }
    };
}
