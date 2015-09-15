/*
 * Copyright (c) Microsoft. All rights reserved. Licensed under the MIT license. See full license at the bottom of this file.
 */

#import "MasterViewController.h"
#import "DetailTableViewController.h"
#import "AuthenticationManager.h"
#import "ConnectViewController.h"
#import "SnippetsManager.h"
#import "Operation.h"

@interface MasterViewController ()

//@property NSMutableArray *objects;
@property (nonatomic, strong) SnippetsManager *snippetManager;

@end

@implementation MasterViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.

    _snippetManager = [[SnippetsManager alloc] init];

    UIBarButtonItem *signOutButton = [[UIBarButtonItem alloc] initWithTitle:@"Disconnect" style:UIBarButtonItemStylePlain target:self action:@selector(signOut:)];
    self.navigationItem.leftBarButtonItem = signOutButton;
    
    self.detailViewController = (DetailViewController *)[[self.splitViewController.viewControllers lastObject] topViewController];
    
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)signOut:(id)sender{
    [[AuthenticationManager sharedInstance] clearCredentials];
    [self dismissViewControllerAnimated:YES completion:^{
        ;
    }];
    
}

#pragma mark - Segues

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    if ([[segue identifier] isEqualToString:@"showDetail"]) {
        NSIndexPath *indexPath = [self.tableView indexPathForSelectedRow];
        DetailTableViewController *controller = (DetailTableViewController *)[[segue destinationViewController] topViewController];
        
        controller.operation = [(self.snippetManager.operationsArray[indexPath.section])[indexPath.row] copy];

        [self.tableView deselectRowAtIndexPath:indexPath animated:YES];
        controller.navigationItem.leftBarButtonItem = self.splitViewController.displayModeButtonItem;
        controller.navigationItem.leftItemsSupplementBackButton = YES;
    }
}

#pragma mark - Table View
- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section{
    return self.snippetManager.sections[section];
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return [self.snippetManager.sections count];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return ((NSArray*)self.snippetManager.operationsArray[section]).count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"Cell" forIndexPath:indexPath];

    Operation *operation = (self.snippetManager.operationsArray[indexPath.section])[indexPath.row];
    cell.textLabel.text = [operation operationName];
    
    if(operation.isAdminRequired)
        cell.detailTextLabel.text = @"Requires admin account";
    else
        cell.detailTextLabel.text = @" ";
        
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    [self performSegueWithIdentifier:@"showDetail" sender:nil];
}

@end


// *********************************************************
//
// O365-iOS-Unified-API-Snippets, https://github.com/OfficeDev/O365-iOS-Unified-API-Snippets
//
// Copyright (c) Microsoft Corporation
// All rights reserved.
//
// MIT License:
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// *********************************************************
