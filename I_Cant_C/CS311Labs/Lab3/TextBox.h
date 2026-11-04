#include <string>

using namespace std;

class TextBox {
    private:
        string value;
    public:
        TextBox();
        TextBox(string val);
        ~TextBox();

        string getValue();
        void setValue(string val);
};