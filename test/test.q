%requires linenoise

my *string $line;

Linenoise::history_set_max_len(10);

# h<TAB> is expanded to string: history
list sub my_callback(string $value) {
    list $ret = ();
    if ($value == 'h')
        push $ret, 'history';
    else if ($value == 'q')
        push $ret, 'quit';

    return $ret;
}

Linenoise::set_callback(\my_callback());

try {
    Linenoise::history_load('history.txt');
}
catch ($ex) {
    printf("History is not loaded: %s - %s\n", $ex.err, $ex.desc);
}


while (True) {
    my *string $line = Linenoise::line("Qore Prompt> ");
    if (!exists $line) {
        printf("^C signal caught. Exiting.\n");
        break;
    }

    if ($line == 'quit') {
        printf("Hi ho!\n");
        break;
    }
    else if ($line == 'help' || $line == '?') {
        printf("commands:\n\thelp\n\tquit\n\thistory\n");
        continue;
    }
    else if ($line == 'history' || $line == 'h') {
        printf("history:\n%N\n", Linenoise::history());
        continue;
    }

    Linenoise::history_add($line);
    printf("OK, doing: '%s'\n", $line);
}

Linenoise::history_save('history.txt');
