#include <FL/Fl.H>
#include <FL/fl_ask.H>
#include <FL/forms.H>
#include <FL/fl_draw.H>
#include <FL/Enumerations.H>
#include <FL/Fl_Double_Window.H>
#include <fmt/base.h>
#include <fmt/format.h>

#include <array>
#include <string>
#include <string_view>

using namespace std;

constexpr char player_x = 'X';
constexpr char player_o = 'O';
constexpr char none = '-';

class Board {
public:
    Board()
    {
        board_.fill(none);
    }

    char get(int x, int y)
    {
        return board_[x * 3 + y];
    }

    void set(int x, int y, char piece)
    {
        board_[x * 3 + y] = piece;
    }

    auto begin() { return board_.begin(); }
    auto begin() const { return board_.begin(); }

    auto end() { return board_.end(); }
    auto end() const { return board_.end(); }

    bool is_win(char piece) const noexcept
    {
        return check_horizontal(piece) || check_vertical(piece) || check_diagonal(piece);
    }

    bool is_full() const noexcept
    {
        for (const auto& piece: board_) {
            if (piece == none)
                return false;
        }
        return true;
    }

private:
    array<char, 9> board_;      // 列主矩阵

    bool check_horizontal(char piece) const noexcept
    {
        for (int i = 0; i < 3; ++i) {
            if (board_[i] == piece && 
                board_[i + 3] == piece && 
                board_[i + 6] == piece)
                return true;
        }

        return false;
    }

    bool check_vertical(char piece) const noexcept
    {
        for (int i = 0; i < 3; ++i) {
            if (board_[i * 3] == piece && 
                board_[i * 3 + 1] == piece && 
                board_[i * 3 + 2] == piece)
                return true;
        }

        return false;
    }

    bool check_diagonal(char piece) const noexcept
    {
        if (board_[0] == piece && board_[4] == piece && board_[8] == piece)
            return true;

        if (board_[2] == piece && board_[4] == piece && board_[6] == piece)
            return true;

        return false;
    }
};


class TicTacToe: public Fl_Double_Window {
public:
    TicTacToe(int width, int height, string title)
      : Fl_Double_Window{ center_x(width), center_y(height), width, height },
        title_{ std::move(title) }
    {
        label(title_.c_str());
        resizable(this);
        end();
    }

    ~TicTacToe() override = default;

    void draw() override
    {
        clear_window();
        draw_message("next player: " + string(1, next_player_));
        draw_board();
        draw_piece();
    }

    int handle(int event) override
    {
        switch (event) {
        case FL_PUSH_BUTTON:
            if (Fl::event_button() == FL_LEFT_MOUSE) {
                const int x = Fl::event_x();
                const int y = Fl::event_y();
                on_clicked(x, y);
                return 1;
            }
        default:
            return Fl_Double_Window::handle(event);
        }
    }

    void title(const string_view new_title) noexcept
    {
        title_ = new_title;
    }

    string_view title() const noexcept { return title_; }

private:
    static constexpr int INTERVAL = 200;
    static constexpr int PADDING = 10;

    string title_;
    Board board_;
    char next_player_ = player_x;

    static int center_x(int width) noexcept
    {
        return Fl::w() / 2 - width / 2;
    }

    static int center_y(int height) noexcept
    {
        return Fl::h() / 2 - height / 2;
    }

    char next_player() noexcept
    {
        auto result = next_player_;
        next_player_ = (next_player_ == player_x) ? player_o : player_x;
        return result;
    }

    void on_clicked(int x, int y)
    {
        const int x_index = x / INTERVAL;
        const int y_index = y / INTERVAL;
        fmt::print("x: {}, y: {}\n", x_index, y_index);

        if (x_index >= 3 || y_index >= 3) return;

        put_chess(x_index, y_index);
    }

    void put_chess(int x, int y)
    {
        char piece = board_.get(x, y);
        if (piece == none) {
            auto player = next_player();
            board_.set(x, y, player);

            redraw();
            check_result(player);
        }
        else {
            auto message = fmt::format("Invalid move! ({}, {})", x, y);
            fmt::println("{}", message);
            fl_message_position(this);
            fl_message(message.c_str());
        }
    }

    void check_result(char player)
    {
        end_if_win(player);
        end_if_draw();
    }

    void end_if_win(char player)
    {
        if (board_.is_win(player)) {
            auto message = fmt::format("Player {} win!", player);
            fmt::println("{}", message);
            fl_message_position(this);
            fl_message(message.c_str());
            Fl::hide_all_windows();
        }
    }

    void end_if_draw()
    {
        if (board_.is_full()) {
            auto message = fmt::format("Draw!");
            fmt::println("{}", message);
            fl_message_position(this);
            fl_message(message.c_str());
            Fl::hide_all_windows();
        }
    }

    void clear_window() const noexcept
    {
        fl_color(FL_BLACK);
        fl_rectf(0, 0, w(), h());
    }

    void draw_board() const
    {
        fl_color(FL_WHITE);
        fl_line_style(FL_SOLID, 2);
        fl_line(0, h() / 3, w(), h() / 3);
        fl_line(0, h() * 2 / 3, w(), h() * 2 / 3);
        fl_line(w() / 3, 0, w() / 3, h());
        fl_line(w() * 2 / 3, 0, w() * 2 / 3, h());
    }

    void draw_piece() const
    {
        int x = 0;
        int y = 0;
        for (auto piece: board_) {
            switch (piece) {
            case player_o:
                draw_o(x, y);
                break;
            case player_x:
                draw_x(x, y);
                break;
            case none:
                break;
            }

            increate_xy(x, y);
        }
    }

    static void increate_xy(int& x, int& y)
    {
        y += INTERVAL;
        if (y >= 600) {
            y = 0;
            x += INTERVAL;
        }
    }

    void draw_x(int x, int y) const
    {
        constexpr int offset = INTERVAL - PADDING;

        fl_color(FL_RED);
        fl_line_style(FL_SOLID, 2);
        fl_line(x + PADDING, y + PADDING, x + offset, y + offset);
        fl_line(x + PADDING, y + offset, x + offset, y + PADDING);
    }

    void draw_o(int x, int y) const
    {
        constexpr int size = 200 - PADDING * 2;
        fl_color(FL_BLUE);
        fl_arc(x + PADDING, y + PADDING, size, size, 0, 360);
    }

    void draw_message(const string_view message) const
    {
        fl_color(FL_YELLOW);
        fl_font(FL_HELVETICA, 16);
        fl_draw(message.data(), PADDING, PADDING * 2);
    }
};


int main(int argc, char* argv[])
{
    TicTacToe window{ 600, 600, "Tic Tac Toe" };

    window.show(argc, argv);
    return Fl::run();
}