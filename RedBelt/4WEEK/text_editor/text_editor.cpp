#include <string>
#include <list>
#include "test_runner.h"

using namespace std;

class Editor {
public:
    using Iter = list<char>::iterator;

    Editor()
    :cursor(text.end())
    {}
    void Left() {
      if(cursor != text.begin()) {--cursor;}
    }
    void Right() {
      if(cursor != text.end()) {++cursor;}
    }
    void Insert(char token) {
      text.insert(cursor, token);
    }
    void Cut(size_t tokens = 1) {
      buff.clear();
      auto finish = Advance(cursor, tokens);
      buff.splice(buff.begin(), text, cursor, finish);
      cursor = finish;
    }
    void Copy(size_t tokens = 1) {
      buff.clear();
      auto temp = cursor;
      while(tokens > 0 && temp != text.end()) {
        buff.emplace_back(*(temp++));
        --tokens;
      }
    }
    void Paste() {
      if (!buff.empty()) {
        text.insert(cursor, buff.begin(), buff.end());
      }
    }

    template <typename It>
    struct for_range {
      for_range(It st, It fi)
      :first(st)
      ,second(fi)
      {}
      It first, second;
      It begin() {return first;}
      const It begin() const {return first;}
      It end() {return second;}
      const It end() const {return second;}
    };

    string GetText() const {
      string temp;
      for_range to (text.begin(), text.end());
      for (auto& letter : to) {
        temp.push_back(letter);
      }
      return temp;
    }
private:
    list<char> text;
    Iter cursor;
    list<char> buff;
    Iter Advance( Iter x, size_t& y) {
      while(y > 0 && x != text.end()) {
        ++x;
        --y;
      }
      return x;
    }
};

void TypeText(Editor& editor, const string& text) {
  for(char c : text) {
    editor.Insert(c);
  }
}

void TestEditing() {
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    editor.Cut(first_part_len);
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    TypeText(editor, ", ");
    editor.Paste();
    editor.Left();
    editor.Left();
    editor.Cut(3);
    
    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;
    
    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();
    
    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }
  
  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");
  
  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);
  return 0;
}