#include "shell.h"

/**
 * _myexit - exits shell
 * @info: Structure containing potential args
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			printError(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory of the process
 * @info: Structure containing potential args.
 *  Return: Always 0
 */
int _mycd(info_t *info)
{
	char *ss, *dire, buffer[1024];
	int chdirRet;

	ss = getcwd(buffer, 1024);
	if (!ss)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dire = _getenv(info, "HOME=");
		if (!dire)
			chdirRet = /* TODO: what should this be? */
				chdir((dire = _getenv(info, "PWD=")) ? dire : "/");
		else
			chdirRet = chdir(dire);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(ss);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdirRet = /* TODO: what should this be? */
			chdir((dire = _getenv(info, "OLDPWD=")) ? dire : "/");
	}
	else
		chdirRet = chdir(info->argv[1]);
	if (chdirRet == -1)
	{
		printError(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - change current dir of process
 * @info: Structure containing potential arguments.
 *  Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **argArray;

	argArray = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*argArray);
	return (0);
}