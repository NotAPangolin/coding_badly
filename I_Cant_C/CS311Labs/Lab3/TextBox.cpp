#include <C:\Users\bmcca\GitHub\coding_badly\I_Cant_C\CS311Labs\Lab2\TextBox.h>

TextBox::TextBox() {
    this->value = "";
}
TextBox::TextBox(string val) {
    this->value = val;
}
//No specific destructor def needed since there is no dynamic memory/pointers in the class
//could do any of following:
TextBox::~TextBox() = default;
// TextBox::~TextBox() {};
// TextBox::~TextBox() {delete this;} // admittedly totally guessing on this one


string TextBox::getValue() {
    return this->value;
}
void TextBox::setValue(string val) {
    this->value = val;
}