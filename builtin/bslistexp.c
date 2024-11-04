// void exenv_help(t_shell *data, char *envp, char *equal, char *quoted)
// {
//     int i;
//     char *key;
//     char *value;
//     char *keystr;
//     int j;

//     //i = 0;
//     j = 0;
//     //while(envp[i])
//     //{
//         // equal = ft_strchr(envp, '=');
//         // if(equal)
//         // {
//             key = ft_substr(envp, 0, envp - equal);
//             value = ft_strdup(equal + 1);
//             quoted = ft_strjoin("\"", value);
//             free(value);
//             value = ft_strjoin(quoted, "\"");
//             free(quoted);

//             keystr = ft_strjoin("declare -x ", key);
//             data->envi[j++] = ft_strjoin(keystr, "=");
//             data->envi[j - 1] = ft_strjoin(data->envi[j - 1], value);
//             free(key);
//             free(value);
//             free(keystr);
//         // }
//     //}
// }

// void our_exenv(t_shell *data, char **envp)
// {
//     int i;
//     int j;
//     char *tmp; 
//     char *equal;
//     char *quoted;
    
//     j = 0;
//     while(envp[j])
//         j++;
//     data->envi = malloc(sizeof(char *) * (j + 1));
//     if(!data->envi)
//         return ;
//     i = 0;
//     while(envp[i])
//     {
//         j = 0;
//         if((equal = ft_strchr(envp[i], '=')))
//         {
//             exenv_help(data, envp[i], equal, quoted);
//             //tmp = ft_strjoin("\"", envp[i]);
//             // tmp = ft_strjoin(envp[i], "\"");
//             // if(!tmp)
//             //     return;
//             // while(tmp[j])
//             //     j++;
//             //tmp = ft_strjoin(&tmp[j], "\"");
//             // data->envi[i] = ft_strjoin("declare -x ", tmp);
//             // free(tmp);
//             // while(envp[i][j])
//             //     j++;
//             // j--;
//             // tmp = &envp[i][j];
//             // data->envi[i][j] = *ft_strjoin(&envp[i][j], "\"");
//             // free(tmp);
//         }
//         else
//         {
//             data->envi[i] = ft_strjoin("declare -x ", envp[i]);
//         }
//         i++;
//     }
//     data->envi[i] = NULL;
// }