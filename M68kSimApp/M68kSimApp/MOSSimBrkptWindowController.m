//
//  MOSSimBrkptWindowController.m
//  Tricky68k
//
//  Created by Daniele Cattaneo on 30/09/15.
//  Copyright © 2015 Daniele Cattaneo. All rights reserved.
//

#import "MOSSimBrkptWindowController.h"
#import "MOSSimulator.h"
#import "MOSMutableBreakpoint.h"


@implementation MOSSimBrkptWindowController


- (instancetype)init {
  self = [super initWithWindowNibName:@"MOSSimBrkptWindow"];
  return self;
}


- (IBAction)cancel:(id)sender {
  [modalWindow endSheet:[self window] returnCode:NSModalResponseCancel];
  modalWindow = nil;
}


- (IBAction)ok:(id)sender {
  [modalWindow endSheet:[self window] returnCode:NSModalResponseOK];
  modalWindow = nil;
}


- (IBAction)addOrRemove:(id)sender {
  if (![sender isKindOfClass:[NSSegmentedControl class]])
    return;
  
  switch ([sender selectedSegment]) {
    case 0:
      [bptsController addObject:[[MOSMutableBreakpoint alloc] initWithAddress:0]];
      break;
    case 1:
      [bptsController remove:sender];
      break;
  }
}


- (void)beginSheetModalForWindow:(NSWindow *)p
               completionHandler:(void (^)(NSModalResponse result))handler {
  NSWindow *w;
  
  if (modalWindow)
    return;
  
  w = [self window];
  modalWindow = p;
  [p beginSheet:w completionHandler:handler];
}


- (void)setBreakpointsFromSet:(NSSet*)b {
  NSMutableArray *conv;
  NSNumber *n;
  MOSMutableBreakpoint *bp;
  
  conv = [[NSMutableArray alloc] init];
  for (n in b) {
    bp = [[MOSMutableBreakpoint alloc] initWithAddress:[n unsignedIntValue]];
    [conv addObject:bp];
  }
  [self setDisplayedBreakpoints:[conv copy]];
}


- (void)setDisplayedBreakpoints:(NSArray *)b {
  breakpts = b;
}


- (NSArray *)displayedBreakpoints {
  return breakpts;
}


@end
