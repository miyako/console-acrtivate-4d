#include "main.h"

static void usage(void)
{
    fprintf(stderr, "Usage: activate-4d [options]\n\n");
		fprintf(stderr, "Activate the 4D v16 MDI window (class name=XTB_MAIN_MDI_58A2D9EE)\n\n");
		fprintf(stderr, " -%c path name: %s\n", OPT_PATH , "specify the application full path (default=any)");
    fprintf(stderr, " -%c class name: %s\n", OPT_CLASS , "specify the class name (default=XTB_MAIN_MDI_58A2D9EE)");
    fprintf(stderr, " -%c : %s\n", OPT_INFORMATION , "display this help and exit");
    exit(1);
}

#ifdef WIN32
int	opterr = 1;
int	optind = 1;
int	optopt;
wchar_t	*optarg;

int getopt(int argc, OPTARG_T *argv, OPTARG_T opts)
{
    static int sp = 1;
    register int c;
    register OPTARG_T cp;
    
    if(sp == 1)
        if(optind >= argc ||
           argv[optind][0] != '-' || argv[optind][1] == '\0')
            return(EOF);
        else if(wcscmp(argv[optind], L"--") == NULL) {
            optind++;
            return(EOF);
        }
    optopt = c = argv[optind][sp];
    if(c == ':' || (cp=wcschr(opts, c)) == NULL) {
        ERR(L": illegal option -- ", c);
        if(argv[optind][++sp] == '\0') {
            optind++;
            sp = 1;
        }
        return('?');
    }
    if(*++cp == ':') {
        if(argv[optind][sp+1] != '\0')
            optarg = &argv[optind++][sp+1];
        else if(++optind >= argc) {
            ERR(L": option requires an argument -- ", c);
            sp = 1;
            return('?');
        } else
            optarg = argv[optind++];
        sp = 1;
    } else {
        if(argv[optind][++sp] == '\0') {
            sp = 1;
            optind++;
        }
        optarg = NULL;
    }
    return(c);
}
#endif

static void doIt(LPCTSTR arg_class, LPCTSTR arg_path)
{
	if(arg_class)
	{
		HWND window = NULL;
		
		do
		{
			window = FindWindowEx(NULL, window, (LPCTSTR)arg_class, NULL);
			if(window)
			{
				if(arg_path)
				{
					DWORD pid;
					GetWindowThreadProcessId(window, &pid);
					HANDLE h=OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
					wchar_t name[MAX_PATH+1];
					if(h)
					{
						GetModuleFileNameEx(h, NULL, name, MAX_PATH);
						CloseHandle(h); 
						if(!lstrcmpi(name, arg_path))
						{
							break;
						}
					}
				}else{
					break;
				}
			}
		}while(window);
	
		ShowWindowAsync(window, SW_RESTORE);
		//ShowWindow(window, SW_RESTORE);
		SetWindowPos(window, HWND_TOP, 0, 0, 0, 0,  SWP_NOMOVE | SWP_NOSIZE);
		//SetActiveWindow(window);
		SetForegroundWindow(window);
		AllowSetForegroundWindow(ASFW_ANY);
		
	}

	exit(0);
}

int main(int argc, OPTARG_T argv[])
{
	wchar_t *arg_class = L"XTB_MAIN_MDI_58A2D9EE";
	wchar_t *arg_path = NULL;

	int ch;
	 
	OPTARG_T output = NULL;
			
	while ((ch = getopt(argc, argv, OPT_LIST)) != -1)
	{
		switch (ch)
		{
			case OPT_PATH:
					arg_path = optarg;
					break;
			case OPT_CLASS:
					arg_class = optarg;
				break;
			case OPT_INFORMATION:
			default:
				usage();
		}
	} 

	doIt(arg_class, arg_path);
    
	return 0;
}
