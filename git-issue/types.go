package main

import (
	"fmt"
)

type Milestone struct {
	Id          int    `json:"id"`
	Title       string `json:"title"`
	Description string `json:"description"`
	DueDate     string `json:"due_date"`
	State       string `json:"state"`
	UpdatedAt   string `json:"updated_at"`
	CreatedAt   string `json:"created_at"`
}

type User struct {
	Id        int    `json:"id"`
	Username  string `json:"username"`
	Email     string `json:"email"`
	Name      string `json:"name"`
	State     string `json:"state"`
	CreatedAt string `json:"created_at"`
}

type Issue struct {
	Id          int        `json:"id"`
	Iid         int        `json:"iid"`
	ProjectId   int        `json:"project_id"`
	Title       string     `json:"title"`
	Description string     `json:"description"`
	Labels      []string   `json:"labels"`
	Milestone   *Milestone `json:"milestone"`
	Assignee    *User      `json:"assignee"`
	Author      *User      `json:"author"`
	State       string     `json:"state"`
	UpdatedAt   string     `json:"updated_at"`
	CreatedAt   string     `json:"created_at"`
}

func (ptr *Issue) String() string {
	return fmt.Sprintf("Issue #%v (%v)> %v", ptr.Id, ptr.State, ptr.Title)
}

func (ptr *Issue) LongString() string {
	msg := fmt.Sprintf("Issue #%v (%v)> %v", ptr.Id, ptr.State, ptr.Title)
	if ptr.Assignee != nil {
		msg += fmt.Sprintf("\nAssignee: %v", ptr.Assignee.Name)
	}
	if ptr.Author != nil {
		msg += fmt.Sprintf("\nAuthor: %v", ptr.Author.Name)
	}
	if ptr.Description != "" {
		msg += fmt.Sprintf("\nDescription:\n%v", ptr.Description)
	}

	return msg
}
