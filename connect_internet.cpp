#include <regex>
#include <unistd.h>
#include <iostream>
#include <cpr/cpr.h>
using namespace std;

bool check_connection()
{
    cpr::Response r = cpr::Get(cpr::Url{"http://google.com"}, cpr::Redirect{false});

    if (r.status_code == 302)
        return false;

    return true;
}

void connect()
{
    string username,
        password;
    cpr::Session sess;

    sess.SetUrl(cpr::Url{"https://sso.ugm.ac.id/cas/login?service=https://internet.ugm.ac.id/sso/login"});
    cpr::Response r = sess.Get();

    regex token("[A-Z0-9]{96}");

    smatch match;
    regex_search(r.text, match, token);

    cout << "==== SSO UGM ====" << endl;
    cout << "Username (without @*.ugm.ac.id)" << endl;
    cout << "> ";
    cin >> username;

    password = getpass("Password: ");

    cpr::Payload payload{
        {"username", username},
        {"password", password},
        {"lt", match.str()},
        {"_eventId", "submit"},
        {"submit", "LOGIN"}};

    sess.SetPayload(payload);

    r = sess.Post();
}

int main()
{
    if (check_connection())
    {
        cout << "Already Connected." << endl;
        exit(1);
    }

    connect();

    if (check_connection())
        cout << "Successfully Connected." << endl;
    else
        cout << "Not Succeed." << endl;

    return 0;
}