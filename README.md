<h1>Minishell <a href="https://github.com/JaeSeoKim/badge42"><img src="https://badge42.vercel.app/api/v2/cl8uf09z900060gl2pg6sdczb/project/2499381" alt="samoreno's 42 minishell Score" /></a></h1>
<h2>Project description</h2>
<div>
<!--  <a href="https://github.com/JaeSeoKim/badge42">
    <img align="center" src="https://badge42.herokuapp.com/api/project/samoreno/ft_printf"/>
  </a> -->
  <p>This is a project at 42 Madrid. The objective of this project is to create a simple shell in bash. This shell should:
  <ul>
    <li>Not interpret unclosed quotes or unspecified special characters like \ or ;</li>
    <li>Not use more than one global variable</li>
    <li>Show a prompt when waiting for a new command</li>
    <li>Have a working History</li>
    <li>Search and launch the right executable (based on the PATH variable or by using relative or absolute path</li>
    <li>It must implement the builtins:</li>
    <ul>
      <li>echo with option -n</li>
      <li>cd with only a relative or absolute path</li>
      <li>pwd with no options</li>
      <li>export with no options</li>
      <li>unset with no options</li>
      <li>env with no options or arguments</li>
      <li>exit with no options</li>
     </ul>
     <li>’ inhibit all interpretation of a sequence of characters</li>
     <li>" inhibit all interpretation of a sequence of characters except for $</li>
     <li>Redirections:</li>
     <ul>
      <li>< should redirect input</li>
      <li>> should redirect output</li>
      <li>“<<” read input from the current source until a line containing only the delimiter is seen. it doesn’t need to update history</li>
      <li>“>>” should redirect output with append mode</li>
     </ul>
     <li>Pipes | The output of each command in the pipeline is connected via a pipe to the</li>
     <li>Environment variables ($ followed by characters) should expand to their values</li>
     <li>$? should expand to the exit status of the most recently executed foreground pipeline</li>
     <li>ctrl-C ctrl-D ctrl-\ should work like in bash</li>
     <li>When interactive:</li>
     <ul>
      <li>ctrl-C print a new prompt on a newline</li>
      <li>ctrl-D exit the shell</li>
      <li>ctrl-\ do nothing</li>
    </ul>
  </ul>
  Readline function can produce some leak but we don’t need to fix this. However, thre rest of the code cannot have leaks. Anything not asked is not required. 
  <table>
    <tr>
      <th>Program name</th>
      <td>minishell</td>
    </tr>
    <tr>
      <th>External C functions allowed</th>
      <td>readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs</td>
    </tr>
    <tr>
      <th>Description</th>
      <td>Write a shell</td>
    </tr>
</table>
</div>
<h2>Usage</h2>
<div>
    <p>
<b>Warning!</b> It is necessary to have the C library "readline" installed
    </p>
    <p>
        With the Makefile you can compile directly. The rules that it allows are:
        <ul>
         <li>Make: it compiles directly</li>
         <li>Make re: if the project is already compiled, it does it again</li>
         <li>Make clean. Deletes all .o files but the executable remains</li>
         <li>make fclean: deletes all .o files and the executable</li>
        </ul>
  Launch the program as follows:<br/>
  <b>./minishell</b>
    </p>
</div>

