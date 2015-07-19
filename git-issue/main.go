package main

import (
	"encoding/json"
	"errors"
	"flag"
	"fmt"
	"github.com/trusch/gogitconfig"
	"io/ioutil"
	"log"
	"net/http"
	URL "net/url"
	"os"
)

var gitlabUri string = ""
var gitlabToken string = ""
var gitlabProjectId string = ""

var list bool = false
var all bool = false
var create bool = false
var get int = -1
var update int = -1
var comment int = -1
var reopenIssue int = -1
var closeIssue int = -1

var title string = ""
var description string = ""

func init() {

	flag.StringVar(&gitlabUri, "uri", "", "uri of your gitlab server")
	flag.StringVar(&gitlabToken, "token", "", "token of your gitlab account")
	flag.StringVar(&gitlabProjectId, "project", "", "project-id of your project")

	//flag.BoolVar(&list, "l", false, "list issues")
	flag.BoolVar(&list, "list", false, "list issues")

	//flag.BoolVar(&create, "c", false, "create an issue")
	flag.BoolVar(&create, "create", false, "create an issue")

	//flag.BoolVar(&all, "a", false, "all issues")
	flag.BoolVar(&all, "all", false, "all issues")

	//flag.IntVar(&get, "g", -1, "get an issue")
	flag.IntVar(&get, "get", -1, "get an issue")

	//flag.IntVar(&update, "u", -1, "update an issue")
	flag.IntVar(&update, "update", -1, "update an issue")

	//flag.IntVar(&comment, "co", -1, "comment an issue")
	flag.IntVar(&comment, "comment", -1, "comment an issue")

	//flag.IntVar(&reopenIssue, "r", -1, "reopen an issue")
	flag.IntVar(&reopenIssue, "reopen", -1, "reopen an issue")

	//flag.IntVar(&closeIssue, "cl", -1, "close an issue")
	flag.IntVar(&closeIssue, "close", -1, "close an issue")

	//flag.StringVar(&title, "t", "", "a title for your issue")
	flag.StringVar(&title, "title", "", "a title for your issue")

	//flag.StringVar(&description, "d", "", "a description for your issue")
	//flag.StringVar(&description, "desc", "", "a description for your issue")
	flag.StringVar(&description, "description", "", "a description for your issue")
}

func getGitOptions() {
	if gitlabUri == "" {
		configKey := gogitconfig.New("gitlab.uri")
		gitlabUri_, err := configKey.Get()
		if err != nil {
			log.Fatal("you need git-config-key 'gitlab.uri'")
		}
		gitlabUri = gitlabUri_
	}
	if gitlabToken == "" {
		configKey := gogitconfig.New("gitlab.token")
		gitlabToken_, err := configKey.Get()
		if err != nil {
			log.Fatal("you need git-config-key 'gitlab.token'")
		}
		gitlabToken = gitlabToken_
	}
	if gitlabProjectId == "" {
		configKey := gogitconfig.New("gitlab.projectid")
		gitlabProjectId_, err := configKey.Get()
		if err != nil {
			log.Fatal("you need git-config-key 'gitlab.projectid'")
		}
		gitlabProjectId = gitlabProjectId_
	}
}

func ListIssues() ([]*Issue, error) {
	url := fmt.Sprintf("%v/api/v3/projects/%v/issues?private_token=%v", gitlabUri, gitlabProjectId, gitlabToken)
	resp, err := http.Get(url)
	if err != nil {
		return nil, err
	}
	defer resp.Body.Close()
	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		return nil, err
	}
	issues := make([]*Issue, 0)
	err = json.Unmarshal(body, &issues)
	if err != nil {
		return nil, err
	}
	return issues, nil
}

func GetIssue(id int) (*Issue, error) {
	url := fmt.Sprintf("%v/api/v3/projects/%v/issues/%v?private_token=%v", gitlabUri, gitlabProjectId, id, gitlabToken)
	resp, err := http.Get(url)
	if err != nil {
		return nil, err
	}
	defer resp.Body.Close()
	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		return nil, err
	}
	issue := Issue{}
	err = json.Unmarshal(body, &issue)
	if err != nil {
		return nil, err
	}
	return &issue, nil
}

func UpdateIssue(id int, title, description string) error {
	url := fmt.Sprintf("%v/api/v3/projects/%v/issues/%v?private_token=%v", gitlabUri, gitlabProjectId, id, gitlabToken)
	if title != "" {
		url += "&title=" + URL.QueryEscape(title)
	}
	if description != "" {
		url += "&description=" + URL.QueryEscape(description)
	}
	req, err := http.NewRequest("PUT", url, nil)
	client := http.Client{}
	resp, err := client.Do(req)
	if err != nil || resp.StatusCode != 200 {
		return errors.New("could not update: request: " + url)
	}
	return nil
}

func CreateIssue(title, description string) error {
	url := fmt.Sprintf("%v/api/v3/projects/%v/issues?private_token=%v", gitlabUri, gitlabProjectId, gitlabToken)
	if title != "" {
		url += "&title=" + URL.QueryEscape(title)
	} else {
		return errors.New("specify a title (-t --title)")
	}
	if description != "" {
		url += "&description=" + URL.QueryEscape(description)
	}
	req, err := http.NewRequest("POST", url, nil)
	client := http.Client{}
	resp, err := client.Do(req)
	if err != nil || resp.StatusCode != 201 {
		return errors.New("could not create: request: " + url)
	}
	return nil
}

func CloseIssue(id int) error {
	url := fmt.Sprintf("%v/api/v3/projects/%v/issues/%v?private_token=%v&state_event=close", gitlabUri, gitlabProjectId, id, gitlabToken)
	req, err := http.NewRequest("PUT", url, nil)
	client := http.Client{}
	resp, err := client.Do(req)
	if err != nil || resp.StatusCode != 200 {
		return errors.New("could not update: request: " + url)
	}
	return nil
}

func ReopenIssue(id int) error {
	url := fmt.Sprintf("%v/api/v3/projects/%v/issues/%v?private_token=%v&state_event=reopen", gitlabUri, gitlabProjectId, id, gitlabToken)
	req, err := http.NewRequest("PUT", url, nil)
	client := http.Client{}
	resp, err := client.Do(req)
	if err != nil || resp.StatusCode != 200 {
		return errors.New("could not update: request: " + url)
	}
	return nil
}

func main() {
	flag.Parse()
	getGitOptions()
	if list {
		issues, err := ListIssues()
		if err != nil {
			log.Fatal(err)
		}
		fmt.Println("-------------------------")
		for _, issue := range issues {
			if all || issue.State == "opened" || issue.State == "reopened" {
				fmt.Println(issue.String())
				fmt.Println("-------------------------")
			}
		}
	} else if get != -1 {
		issue, err := GetIssue(get)
		if err != nil {
			log.Fatal(err)
		}
		fmt.Println("-------------------------")
		fmt.Println(issue.LongString())
		fmt.Println("-------------------------")
	} else if update != -1 {
		err := UpdateIssue(update, title, description)
		if err != nil {
			log.Println(err)
			os.Exit(1)
		}
	} else if create {
		err := CreateIssue(title, description)
		if err != nil {
			log.Println(err)
			os.Exit(1)
		}
	} else if closeIssue != -1 {
		err := CloseIssue(closeIssue)
		if err != nil {
			log.Println(err)
			os.Exit(1)
		}
	} else if reopenIssue != -1 {
		err := ReopenIssue(reopenIssue)
		if err != nil {
			log.Println(err)
			os.Exit(1)
		}
	} else {
		flag.PrintDefaults()
		PrintCompletions("git-issue")
		os.Exit(1)
	}
}
