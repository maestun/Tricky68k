//
//  MOSDescribeFontTransformer.h
//  Tricky68k
//
//  Created by Daniele Cattaneo on 21/04/15.
//  Copyright (c) 2015 Daniele Cattaneo. 
//

#import <Cocoa/Cocoa.h>


@interface MOSDescribeArchivedFontTransformer : NSValueTransformer {
  NSNumberFormatter *ptSizeFormatter;
}

@end
