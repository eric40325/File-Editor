#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

int choice;
string filename;
fstream file;
string content;                              ///檔案內容
int line, sentence, word, character, symbol; ///行數、句數、單字數、字元數、符號數
bool p = 0;                                  ///關閉程式指令

void open_file();                ///開啟/新增檔案
bool open_file_choice(int);      ///開啟/新增檔案選項選擇後
void analyze_file();             ///文件分析
void deal_with_file();           ///文件分析完之後
bool deal_with_file_choice(int); ///操作文件
bool edit_choice(int);           ///新增/修改文字
char int_to_char(int);           ///非常硬幹的把字元0~9轉為數值0~9  的函數
bool insert_choice(int);         ///插入/刪除行數
bool show_choice(int);           ///顯示內容
void search_contents();          ///尋找單字
bool save_choice(int);           ///儲存/不儲存檔案

///主程式
int main()
{
    open_file();      ///開啟/新增檔案
    analyze_file();   ///分析檔案
    deal_with_file(); ///分析完檔案之後
    return 0;
}

///開啟/新增檔案
void open_file()
{
    cout << "\n<< File Editor >>";
    while (1)
    {
        cout << "\n=============================\n\n[1] Open\n[2] New\n[3] Exit\nChoice: ";
        cin >> choice;
        if (open_file_choice(choice) == 1)
            return;
    }
}

///開啟/新增檔案選項選擇後
bool open_file_choice(int choice)
{
    switch (choice)
    {
    ///開啟檔案
    case 1:
        cout << "File name: ";
        cin >> filename;
        file.open(filename.c_str());
        ///若檔案不存在
        if (!file.is_open())
            cout << "\"" << filename << "\" doesn't exist!";
        return file.is_open();
    ///新增檔案
    case 2:
        cout << "File name: ";
        cin >> filename;
        file.open(filename.c_str(), ios::out | ios::trunc);
        file.close();
        file.open(filename.c_str());
        return 1;
    ///結束程式
    case 3:
        cout << "\n=============================\n\nGoodBye!\n";
        p = 1;
        return 1;
    default:
        cout << "Invalid input!";
        return 0;
    }
}

///文件分析
void analyze_file()
{
    if (p == 1)
        return;
    string temp; ///暫存區
    cout << endl
         << filename << " - Properties:"
         << "\n=============================";
    line = sentence = word = character = symbol = 0; ///初始化
    ///讀檔+計算行數
    for (; !file.eof(); line++)
    {
        getline(file, temp);
        content += (temp + "\n");
    }
    content.erase(content.length() - 1, 1); ///刪除多餘的換行
    ///針對測資2及新增檔案(避免檔案最後為空行
    if (content[content.length() - 1] == '\n' || content.empty())
        line--;
    cout << endl
         << line << left << "\tline";
    ///單字單複數控制
    if (line >= 2)
        cout << "s";
    ///計算句數
    size_t sentence_pos = content.find(".");
    for (; sentence_pos != string::npos; sentence++)
        sentence_pos = content.find(".", sentence_pos + 1);
    cout << endl
         << sentence << left << "\tsentence";
    ///單字單複數控制
    if (sentence >= 2)
        cout << "s";
    ///計算單字數
    size_t word_pos = content.find_first_of("1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM'");
    size_t end_pos = content.find_first_not_of("1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM'", word_pos + 1);
    for (; word_pos != string::npos; word++)
    {
        word_pos = content.find_first_of("1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM'", end_pos + 1);
        end_pos = content.find_first_not_of("1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM'", word_pos + 1);
    }
    cout << endl
         << word << left << "\tword";
    ///單字單複數控制
    if (word >= 2)
        cout << "s";
    ///計算字元數
    size_t character_pos = content.find_first_of("1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM");
    for (; character_pos != string::npos; character++)
        character_pos = content.find_first_of("1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM", character_pos + 1);
    cout << endl
         << character << left << "\tcharacter";
    ///單字單複數控制
    if (character >= 2)
        cout << "s";
    ///計算符號數
    int space = 0;
    size_t space_pos = content.find(" ");
    for (; space_pos != string::npos; space++)
        space_pos = content.find(" ", space_pos + 1);
    symbol = content.length() - line + 1 - character - space;
    ///針對測資2及新增檔案(避免檔案最後為空行
    if (content[content.length() - 1] == '\n' || content.empty())
        symbol--;
    cout << endl
         << symbol << left << "\tsymbol";
    ///單字單複數控制
    if (symbol >= 2)
        cout << "s";
    return;
}

///文件分析完之後
void deal_with_file()
{
    if (p == 1)
        return;
    while (1)
    {
        cout << "\n=============================\nWhat do you want to do?\n\n[1] Edit Contents\n[2] Insert/Delete Line Number\n[3] Show Contents\n[4] Search Contents\n[5] Exit\nChoice: ";
        cin >> choice;
        if (deal_with_file_choice(choice) == 1)
            return;
    }
}

///操作文件
bool deal_with_file_choice(int choice)
{
    switch (choice)
    {
    ///新增/修改文字
    case 1:
        while (1)
        {
            cout << "\n=============================\nFunction:\n\n[1] Insert Somewhere\n[2] Replace Somewhere\n[3] Delete Somewhere\n[4] Replace All\n[5] Delete All\n[6] Exit\nChoice: ";
            cin >> choice;
            if (edit_choice(choice) == 1)
                return 0;
        }
    ///插入/刪除行數
    case 2:
        if (content.empty())
        {
            cout << "=============================\n\"" << filename << "\" is empty!";
            return 0;
        }
        while (1)
        {
            cout << "\n=============================\n\n[1] Insert\n[2] Delete\n[3] Exit\nChoice: ";
            cin >> choice;
            if (insert_choice(choice) == 1)
                return 0;
        }
    ///顯示內容
    case 3:
        if (content.empty())
        {
            cout << "=============================\n\"" << filename << "\" is empty!";
            return 0;
        }
        while (1)
        {
            cout << "\n=============================\n\n[1] All Contents\n[2] One Line\n[3] One Line to Another\n[4] One Sentence\n[5] One Sentence to Another\n[6] Exit\nChoice: ";
            cin >> choice;
            if (show_choice(choice) == 1)
                return 0;
        }
    ///尋找單字
    case 4:
        if (content.empty())
        {
            cout << "=============================\n\"" << filename << "\" is empty!";
            return 0;
        }
        cout << "\n=============================\n";
        search_contents();
        return 0;
    ///儲存/不儲存檔案
    case 5:
        while (1)
        {
            cout << "\n=============================\nSave the file?\n\n[1] Yes\n[2] No\n[3] Cancel\nChoice: ";
            cin >> choice;
            if (save_choice(choice) == 1)
                break;
        }
        if (p == 1)
        {
            cout << "\n=============================\n\nGoodBye!\n";
            return 1;
        }
        else
            return 0;
    default:
        cout << "Invalid input!";
        return 0;
    }
}

///新增/修改文字
bool edit_choice(int choice)
{
    int x, y; ///輸入的數字
    int counter;
    string a, b;                         ///輸入的字串
    size_t start_pos, end_pos, edit_pos; ///起始位置、結束位置、編輯位置
    switch (choice)
    {
    ///某行某位置插入
    case 1:
        cout << "Enter the two numbers of line and position: ";
        cin >> x >> y;
        ///行數輸入錯誤
        while (x < 1 || y < 1)
        {
            cout << "Invalid input!\n\nEnter the two numbers of line and position: ";
            cin >> x >> y;
        }
        cout << "Enter the string to insert: ";
        cin >> a;
        ///行數超過
        if (x > line && x != 1)
        {
            cout << "Line " << x << " doesn't exist!";
            return 0;
        }
        ///找start_pos
        if (x == 1)
            start_pos = -1;
        else
        {
            start_pos = content.find("\n");
            for (counter = x; counter - 2 >= 1; counter--)
                start_pos = content.find("\n", start_pos + 1);
        }
        ///找end_pos
        if ((x == line && content[content.length() - 1] != '\n') || (x == 1 && content.empty()))
            end_pos = content.length();
        else
            end_pos = content.find("\n", start_pos + 1);
        ///位置超過
        if (y > end_pos - start_pos)
        {
            cout << "Position " << y << " doesn't exist!";
            return 0;
        }
        content.insert(start_pos + y, a);
        ///針對編輯空文件
        if (line == 0)
            line++;
        cout << "Insert successfully!";
        return 1;
    ///某行某位置取代
    case 2:
        if (content.empty())
        {
            cout << "=============================\n\"" << filename << "\" is empty!";
            return 0;
        }
        cout << "Enter the number of line and the string: ";
        cin >> x >> a;
        ///行數輸入錯誤
        while (x < 1)
        {
            cout << "Invalid input!\n\nEnter the number of line and the string: ";
            cin >> x >> a;
        }
        cout << "Enter the string to replace: ";
        cin >> b;
        ///行數超過
        if (x > line)
        {
            cout << "Line " << x << " doesn't exist!";
            return 0;
        }
        ///找start_pos
        if (x == 1)
            start_pos = -1;
        else
        {
            start_pos = content.find("\n");
            for (counter = x; counter - 2 >= 1; counter--)
                start_pos = content.find("\n", start_pos + 1);
        }
        ///找end_pos
        if (x == line && content[content.length() - 1] != '\n')
            end_pos = content.length();
        else
            end_pos = content.find("\n", start_pos + 1);
        edit_pos = content.find(a, start_pos + 1);
        ///位置超過或找不到
        if (edit_pos > end_pos || edit_pos == string::npos)
        {
            cout << "String \"" << a << "\" doesn't exist!";
            return 0;
        }
        content.replace(edit_pos, a.length(), b);
        cout << "Replace successfully!";
        return 1;
    ///某行某位置刪除
    case 3:
        if (content.empty())
        {
            cout << "=============================\n\"" << filename << "\" is empty!";
            return 0;
        }
        cout << "Enter the number of line and the string: ";
        cin >> x >> a;
        ///行數輸入錯誤
        while (x < 1)
        {
            cout << "Invalid input!\n\nEnter the number of line and the string: ";
            cin >> x >> a;
        }
        ///行數超過
        if (x > line)
        {
            cout << "Line " << x << " doesn't exist!";
            return 0;
        }
        ///找start_pos
        if (x == 1)
            start_pos = -1;
        else
        {
            start_pos = content.find("\n");
            for (counter = x; counter - 2 >= 1; counter--)
                start_pos = content.find("\n", start_pos + 1);
        }
        ///找end_pos
        if (x == line && content[content.length() - 1] != '\n')
            end_pos = content.length();
        else
            end_pos = content.find("\n", start_pos + 1);
        edit_pos = content.find(a, start_pos + 1);
        ///位置超過或找不到
        if (edit_pos > end_pos || edit_pos == string::npos)
        {
            cout << "String \"" << a << "\" doesn't exist!";
            return 0;
        }
        content.erase(edit_pos, a.length());
        cout << "Delete successfully!";
        return 1;
    ///全部取代
    case 4:
        if (content.empty())
        {
            cout << "=============================\n\"" << filename << "\" is empty!";
            return 0;
        }
        cout << "Enter the string: ";
        cin >> a;
        cout << "Enter the string to replace: ";
        cin >> b;
        edit_pos = content.find(a);
        ///找不到
        if (edit_pos == string::npos)
        {
            cout << "String \"" << a << "\" doesn't exist!";
            return 0;
        }
        ///取代
        for (counter = 0; edit_pos != string::npos; counter++)
        {
            content.replace(edit_pos, a.length(), b);
            edit_pos = content.find(a, edit_pos + b.length());
        }
        cout << "Replace successfully! Totally replace " << counter << " \"" << a << "\" !";
        return 1;
    ///全部刪除
    case 5:
        if (content.empty())
        {
            cout << "=============================\n\"" << filename << "\" is empty!";
            return 0;
        }
        cout << "Enter the string: ";
        cin >> a;
        edit_pos = content.find(a);
        ///找不到
        if (edit_pos == string::npos)
        {
            cout << "String \"" << a << "\" doesn't exist!";
            return 0;
        }
        ///刪除
        for (counter = 0; edit_pos != string::npos; counter++)
        {
            content.erase(edit_pos, a.length());
            edit_pos = content.find(a, edit_pos);
        }
        cout << "Delete successfully! Totally delete " << counter << " \"" << a << "\" !";
        return 1;
    ///跳出不執行
    case 6:
        return 1;
    default:
        cout << "Invalid input!";
        return 0;
    }
}

///插入/刪除行數
bool insert_choice(int choice)
{
    string line_number;   ///輸出的行數
    size_t line_pos = -1; ///輸出位置初始化
    switch (choice)
    {
    ///輸出行數+\t
    case 1:
        if (content.empty())
        {
            cout << "\"" << filename << "\" is empty!";
            return 1;
        }
        for (int number = 1; number <= line; number++)
        {
            line_number.clear();
            ///行數:int->char->string，最後存入line_number
            for (int temp = number; temp >= 1; temp /= 10)
                line_number.insert(0, 1, int_to_char(temp % 10));
            content.insert(line_pos + 1, line_number + "\t");
            line_pos = content.find("\n", line_pos + line_number.length() + 2);
        }
        cout << "Insert successfully!";
        return 1;
    ///刪除行數+\t
    case 2:
        if (content.empty())
        {
            cout << "\"" << filename << "\" is empty!";
            return 1;
        }
        for (int number = 1, length = 0; number <= line; number++, length = 0)
        {
            ///確認刪除字元數
            for (int temp = number; temp >= 1; temp /= 10, length++)
                continue;
            content.erase(line_pos + 1, length + 1);
            line_pos = content.find("\n", line_pos + 1);
        }
        cout << "Delete successfully!";
        return 1;
    ///不執行跳出
    case 3:
        return 1;
    default:
        cout << "Invalid input!";
        return 0;
    }
}

///非常硬幹的把字元0~9轉為數值0~9  的函數
char int_to_char(int x)
{
    char y;
    if (x == 1)
        y = '1';
    else if (x == 2)
        y = '2';
    else if (x == 3)
        y = '3';
    else if (x == 4)
        y = '4';
    else if (x == 5)
        y = '5';
    else if (x == 6)
        y = '6';
    else if (x == 7)
        y = '7';
    else if (x == 8)
        y = '8';
    else if (x == 9)
        y = '9';
    else
        y = '0';
    return y;
}

///顯示內容
bool show_choice(int choice)
{
    int x, y; ///輸入的數字
    int counter;
    size_t start_pos, end_pos, edit_pos; ///起始位置、結束位置、編輯位置
    switch (choice)
    {
    ///全部顯示
    case 1:
        cout << endl
             << filename << " - Contents:"
             << "\n=============================\n"
             << content;
        return 1;
    ///顯示某行
    case 2:
        cout << "Enter the number of line: ";
        cin >> x;
        ///行數輸入錯誤
        while (x < 1)
        {
            cout << "Invalid input!\n\nEnter the number of line: ";
            cin >> x;
        }
        ///行數超過
        if (x > line)
        {
            cout << "Line " << x << " doesn't exist!";
            return 0;
        }
        ///找start_pos
        if (x == 1)
            start_pos = -1;
        else
        {
            start_pos = content.find("\n");
            for (counter = x; counter - 2 >= 1; counter--)
                start_pos = content.find("\n", start_pos + 1);
        }
        ///找end_pos
        if (x == line && content[content.length() - 1] != '\n')
            end_pos = content.length();
        else
            end_pos = content.find("\n", start_pos + 1);
        cout << endl
             << filename << " - Contents of "
             << "line " << x << ":"
             << "\n=============================\n"
             << content.substr(start_pos + 1, end_pos - start_pos - 1);
        return 1;
    ///顯示某行到某行
    case 3:
        cout << "Enter the two numbers of lines: ";
        cin >> x >> y;
        ///行數輸入錯誤
        while (x < 1 || y < x)
        {
            cout << "Invalid input!\n\nEnter the two numbers of lines: ";
            cin >> x >> y;
        }
        ///行數超過
        if (x > line)
        {
            cout << "Line " << x << " doesn't exist!";
            return 0;
        }
        ///找start_pos
        if (x == 1)
            start_pos = -1;
        else
        {
            start_pos = content.find("\n");
            for (counter = x; counter - 2 >= 1; counter--)
                start_pos = content.find("\n", start_pos + 1);
        }
        ///找end_pos
        if (y >= line && content[content.length() - 1] != '\n')
            end_pos = content.length();
        else
        {
            end_pos = content.find("\n", start_pos + 1);
            ///行數超過->顯示至文件結尾
            if (y >= line)
                for (counter = line - x; counter >= 1; counter--)
                    end_pos = content.find("\n", end_pos + 1);
            else
                for (counter = y - x; counter >= 1; counter--)
                    end_pos = content.find("\n", end_pos + 1);
        }
        cout << endl
             << filename << " - Contents of "
             << "line " << x << " to line " << y << ":"
             << "\n=============================\n"
             << content.substr(start_pos + 1, end_pos - start_pos - 1);
        return 1;
    ///顯示某句
    case 4:
        cout << "Enter the number of sentence: ";
        cin >> x;
        ///句數輸入錯誤
        while (x < 1)
        {
            cout << "Invalid input!\n\nEnter the number of sentence: ";
            cin >> x;
        }
        ///句數超過
        if (x > sentence)
        {
            cout << "Sentence " << x << " doesn't exist!";
            return 0;
        }
        ///找start_pos
        if (x == 1)
            start_pos = -1;
        else
        {
            start_pos = content.find(".");
            for (counter = x; counter - 2 >= 1; counter--)
                start_pos = content.find(".", start_pos + 1);
            start_pos = content.find_first_of("1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM", start_pos + 1) - 1;
        }
        ///找end_pos
        if (x == sentence && content[content.length() - 1] != '\n')
            end_pos = content.length();
        else
            end_pos = content.find(".", start_pos + 1) + 1;
        cout << endl
             << filename << " - Contents of "
             << "sentence " << x << ":"
             << "\n=============================\n"
             << content.substr(start_pos + 1, end_pos - start_pos - 1);
        return 1;
    ///顯示某句到某句
    case 5:
        cout << "Enter the two numbers of sentences: ";
        cin >> x >> y;
        ///句數輸入錯誤
        while (x < 1 || y < x)
        {
            cout << "Invalid input!\n\nEnter the two numbers of sentences: ";
            cin >> x >> y;
        }
        ///句數超過
        if (x > sentence)
        {
            cout << "Sentence " << x << " doesn't exist!";
            return 0;
        }
        ///找start_pos
        if (x == 1)
            start_pos = -1;
        else
        {
            start_pos = content.find(".");
            for (counter = x; counter - 2 >= 1; counter--)
                start_pos = content.find(".", start_pos + 1);
            start_pos = content.find_first_of("1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM", start_pos + 1) - 1;
        }
        ///找end_pos
        if (y >= sentence && content[content.length() - 1] != '\n')
            end_pos = content.length();
        else
        {
            end_pos = content.find(".", start_pos + 1) + 1;
            ///句數超過顯示至文章結尾
            if (y >= sentence)
                for (counter = sentence - x; counter >= 1; counter--)
                    end_pos = content.find(".", end_pos) + 1;
            else
                for (counter = y - x; counter >= 1; counter--)
                    end_pos = content.find(".", end_pos) + 1;
        }
        cout << endl
             << filename << " - Contents of "
             << "sentence " << x << " to sentence " << y << ":"
             << "\n=============================\n"
             << content.substr(start_pos + 1, end_pos - start_pos - 1);
        return 1;
    ///跳出不執行
    case 6:
        return 1;
    default:
        cout << "Invalid input!";
        return 0;
    }
}

///尋找單字
void search_contents()
{
    string search_word; ///欲搜尋的單字
    int result = 0;     ///搜尋到的單字數
    cout << "Enter the word to search: ";
    cin >> search_word;
    cout << "\nResult:";
    size_t hard_point = search_word.find_first_not_of("1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM'");
    size_t start_pos = content.find_first_of("1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM'");
    size_t end_pos = content.find_first_not_of("1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM'", start_pos + 1);
    ///針對插入內容後的空白文件(只有單字
    if (end_pos == string::npos)
        end_pos = content.length();
    ///無萬用字元->一般搜尋
    if (hard_point == string::npos)
        while (start_pos != string::npos)
        {
            if (search_word == content.substr(start_pos, end_pos - start_pos))
            {
                cout << " " << content.substr(start_pos, end_pos - start_pos);
                result++;
            }
            start_pos = content.find_first_of("1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM'", end_pos + 1);
            end_pos = content.find_first_not_of("1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM'", start_pos + 1);
            if (end_pos == string::npos)
                end_pos = content.length();
        }
    ///找不到
    if (result == 0)
        cout << " No result!";
    else
    {
        cout << ", " << result << " result";
        ///單字單複數控制
        if (result >= 2)
            cout << "s";
        cout << " totally.";
    }
    return;
}

///儲存/不儲存檔案
bool save_choice(int choice)
{
    switch (choice)
    {
    ///儲存
    case 1:
        file.close();
        file.open(filename.c_str());
        file << content;
        file.close();
        cout << "Save successfully!";
        p = 1;
        return 1;
    ///不儲存
    case 2:
        p = 1;
        return 1;
    case 3:
        return 1;
    default:
        cout << "Invalid input!";
        return 0;
    }
}
