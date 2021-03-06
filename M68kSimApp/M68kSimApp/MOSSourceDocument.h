//
//  Document.h
//  M68kSimApp
//
//  Created by Daniele Cattaneo on 29/12/14.
//  Copyright (c) 2014 Daniele Cattaneo. 
//

#import <Cocoa/Cocoa.h>
#import <Quartz/Quartz.h>
#include "MOSDocument.h"


@class MGSFragariaView;
@class MGSTextView;
@class MOSAssembler;
@class MOSSimulatorViewController;
@class MOSFragariaPreferencesObserver;
@class MOSJob;
@class MOSPlatform;
@class MOSSourceBreakpointDelegate;
@class MOSListingDictionary;


@interface MOSSourceDocument : MOSDocument {
  /* AppKit already has a private window outlet, but it's not exposed
   * because NSDocument also supports multiple windows for the same document.
   * But, since we don't support that, it's just an annoyance. */
  __weak IBOutlet NSWindow *docWindow;
  
  NSTextStorage *text;
  MGSTextView *textView;
  IBOutlet MGSFragariaView *fragaria;
  MOSFragariaPreferencesObserver *prefobs;
  MOSSourceBreakpointDelegate *breakptdel;
  
  MOSPlatform *platform;
  IBOutlet MOSSimulatorViewController *simVc;
  NSView *simView;
  __weak NSResponder *lastSimViewFirstResponder;
  
  BOOL assembleForSaveOnly;
  MOSJob *lastJob;
  BOOL hadJob;
  /* Following ivars must not be modified if assembleForSaveOnly == YES: */
  NSTextStorage *lastSource;
  MOSListingDictionary *lastListing;
}

- (IBAction)assemble:(id)sender;
- (IBAction)assembleAndRun:(id)sender;
- (IBAction)assembleAndSaveAs:(id)sender;
- (IBAction)switchToSimulator:(id)sender;
- (IBAction)switchToEditor:(id)editor;

- (void)simulatorModeShouldTerminate:(id)sender;
- (BOOL)simulatorModeSwitchAllowed;
- (BOOL)sourceModeSwitchAllowed;

- (void)breakpointsShouldSyncFromSimulator:(id)sender;
- (void)breakpointsShouldSyncToSimulator:(id)sender;

- (MOSPlatform *)currentPlatform;

@end

